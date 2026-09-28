#include <gtest/gtest.h>

#include <initializer_list>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "expressions/assign_expr.hpp"
#include "expressions/binary_expr.hpp"
#include "expressions/call_expr.hpp"
#include "expressions/cast_expr.hpp"
#include "expressions/comma_expr.hpp"
#include "expressions/conditional_expr.hpp"
#include "expressions/field_expr.hpp"
#include "expressions/index_expr.hpp"
#include "expressions/literal_expr.hpp"
#include "expressions/name_expr.hpp"
#include "expressions/sizeof_expr.hpp"
#include "expressions/unary_expr.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "statements/block_stmt.hpp"
#include "statements/break_stmt.hpp"
#include "statements/continue_stmt.hpp"
#include "statements/do_while_stmt.hpp"
#include "statements/enum_decl.hpp"
#include "statements/expression_stmt.hpp"
#include "statements/for_stmt.hpp"
#include "statements/function_decl.hpp"
#include "statements/if_stmt.hpp"
#include "statements/return_stmt.hpp"
#include "statements/struct_decl.hpp"
#include "statements/var_decl_stmt.hpp"
#include "statements/while_stmt.hpp"
#include "visitor.hpp"

namespace
{
// Prints a tree as an S-expression, so `1 + 2 * 3` becomes (+ 1 (* 2 3)) and
// `while (x) y;` becomes (while x y;). Expression statements print as the expression plus `;`,
// and a missing optional part (like an empty for clause) prints as `_`.
class AstPrinter : public jm::ExprVisitor, public jm::StmtVisitor
{
public:
  std::string print(jm::Expr* expr)
  {
    if (expr == nullptr) return "<null>";
    expr->accept(*this);
    return result_;
  }

  std::string print(jm::Stmt* stmt)
  {
    if (stmt == nullptr) return "<null>";
    stmt->accept(*this);
    return result_;
  }

  void visitBinaryExpr(jm::BinaryExpr& expr) override
  {
    result_ = list(expr.op.lexeme, {expr.left.get(), expr.right.get()});
  }

  void visitUnaryExpr(jm::UnaryExpr& expr) override
  {
    result_ = list(expr.op.lexeme, {expr.right.get()});
  }

  void visitLiteralExpr(jm::LiteralExpr& expr) override
  {
    result_ = std::string(expr.value.lexeme);
  }

  void visitNameExpr(jm::NameExpr& expr) override
  {
    result_ = std::string(expr.name.lexeme);
  }

  void visitCallExpr(jm::CallExpr& expr) override
  {
    std::vector<jm::Expr*> children{expr.callee.get()};
    for (auto& argument : expr.arguments) children.push_back(argument.get());
    result_ = list("call", children);
  }

  void visitIndexExpr(jm::IndexExpr& expr) override
  {
    result_ = list("index", {expr.object.get(), expr.index.get()});
  }

  void visitFieldExpr(jm::FieldExpr& expr) override
  {
    result_ = "(" + std::string(expr.op.lexeme) + " " + print(expr.object.get()) + " " +
              std::string(expr.field.lexeme) + ")";
  }

  void visitCastExpr(jm::CastExpr& expr) override
  {
    result_ = "(cast " + typeName(expr.type) + " " + print(expr.expr.get()) + ")";
  }

  void visitSizeofExpr(jm::SizeofExpr& expr) override
  {
    if (expr.type)
      result_ = "(sizeof " + typeName(*expr.type) + ")";
    else
      result_ = list("sizeof", {expr.expr.get()});
  }

  void visitConditionalExpr(jm::ConditionalExpr& expr) override
  {
    result_ = list("?:", {expr.condition.get(), expr.thenExpr.get(), expr.elseExpr.get()});
  }

  void visitCommaExpr(jm::CommaExpr& expr) override
  {
    std::vector<jm::Expr*> children;
    for (auto& child : expr.expressions) children.push_back(child.get());
    result_ = list(",", children);
  }

  void visitAssignExpr(jm::AssignExpr& expr) override
  {
    result_ = list(expr.op.lexeme, {expr.target.get(), expr.value.get()});
  }

  void visitExpressionStmt(jm::ExpressionStmt& stmt) override
  {
    result_ = stmt.expr == nullptr ? ";" : print(stmt.expr.get()) + ";";
  }

  void visitBlockStmt(jm::BlockStmt& stmt) override
  {
    std::string out = "(block";
    for (auto& child : stmt.statements) out += " " + print(child.get());
    result_ = out + ")";
  }

  void visitIfStmt(jm::IfStmt& stmt) override
  {
    std::string out = "(if " + print(stmt.condition.get()) + " " + print(stmt.thenBranch.get());
    if (stmt.elseBranch != nullptr) out += " " + print(stmt.elseBranch.get());
    result_ = out + ")";
  }

  void visitWhileStmt(jm::WhileStmt& stmt) override
  {
    result_ = "(while " + print(stmt.condition.get()) + " " + print(stmt.body.get()) + ")";
  }

  void visitDoWhileStmt(jm::DoWhileStmt& stmt) override
  {
    result_ = "(do " + print(stmt.body.get()) + " " + print(stmt.condition.get()) + ")";
  }

  void visitForStmt(jm::ForStmt& stmt) override
  {
    std::string init = stmt.init == nullptr ? "_" : print(stmt.init.get());
    result_ = "(for " + init + " " + optional(stmt.condition.get()) + " " +
              optional(stmt.increment.get()) + " " + print(stmt.body.get()) + ")";
  }

  void visitBreakStmt(jm::BreakStmt&) override
  {
    result_ = "(break)";
  }

  void visitContinueStmt(jm::ContinueStmt&) override
  {
    result_ = "(continue)";
  }

  void visitReturnStmt(jm::ReturnStmt& stmt) override
  {
    result_ = stmt.value == nullptr ? "(return)" : "(return " + print(stmt.value.get()) + ")";
  }

  void visitVarDeclStmt(jm::VarDeclStmt& stmt) override
  {
    std::string out = "(var " + typeName(stmt.type) + " " + std::string(stmt.name.lexeme);
    if (stmt.initializer != nullptr) out += " " + print(stmt.initializer.get());
    result_ = out + ")";
  }

  void visitFunctionDecl(jm::FunctionDecl& stmt) override
  {
    std::string params;
    for (auto& param : stmt.params)
    {
      if (!params.empty()) params += " ";
      params += "(" + typeName(param.type) + " " + std::string(param.name.lexeme) + ")";
    }
    std::string out = "(fn " + typeName(stmt.returnType) + " " + std::string(stmt.name.lexeme) +
                      " (" + params + ")";
    if (stmt.body != nullptr) out += " " + print(stmt.body.get());
    result_ = out + ")";
  }

  void visitStructDecl(jm::StructDecl& stmt) override
  {
    std::string out = "(struct " + std::string(stmt.name.lexeme);
    for (auto& field : stmt.fields)
      out += " (" + typeName(field.type) + " " + std::string(field.name.lexeme) + ")";
    result_ = out + ")";
  }

  void visitEnumDecl(jm::EnumDecl& stmt) override
  {
    std::string out = "(enum " + std::string(stmt.name.lexeme);
    for (auto& enumerator : stmt.enumerators)
    {
      std::string name(enumerator.name.lexeme);
      out += enumerator.value == nullptr ? " " + name
                                         : " (" + name + " " + print(enumerator.value.get()) + ")";
    }
    result_ = out + ")";
  }

private:
  std::string result_;

  std::string optional(jm::Expr* expr)
  {
    return expr == nullptr ? "_" : print(expr);
  }

  std::string list(std::string_view head, const std::vector<jm::Expr*>& children)
  {
    std::string out = "(" + std::string(head);
    for (jm::Expr* child : children) out += " " + print(child);
    return out + ")";
  }

  static std::string typeName(const jm::Type& type)
  {
    return std::string(type.name.lexeme) + std::string(type.pointerDepth, '*');
  }
};

// Tokens, and the nodes built from them, hold string_views into `source`, so it has to outlive
// the returned tree. String literals always do.
std::vector<std::unique_ptr<jm::Stmt>> parse(std::string_view source)
{
  jm::Lexer lexer(source);
  jm::Parser parser(lexer.tokenize());
  return parser.parse();
}

// The expression of the only statement parsed, or nullptr if that isn't a single expression
// statement.
jm::Expr* onlyExpr(const std::vector<std::unique_ptr<jm::Stmt>>& statements)
{
  if (statements.size() != 1) return nullptr;
  auto* statement = dynamic_cast<jm::ExpressionStmt*>(statements[0].get());
  return statement == nullptr ? nullptr : statement->expr.get();
}

// Parses a single expression statement such as "a + b;" and prints its expression.
std::string parseExpr(std::string_view source)
{
  auto statements = parse(source);
  jm::Expr* expr = onlyExpr(statements);
  if (expr == nullptr) return "<not a single expression statement>";
  return AstPrinter().print(expr);
}

// Everything the parser reported to stderr while parsing `source`.
std::string parseErrors(std::string_view source)
{
  testing::internal::CaptureStderr();
  parse(source);
  return testing::internal::GetCapturedStderr();
}

bool reportsError(std::string_view source)
{
  return parseErrors(source).find("ParseError") != std::string::npos;
}

// Parses `source` and prints every statement, separated by spaces.
std::string parseStmts(std::string_view source)
{
  auto statements = parse(source);
  AstPrinter printer;
  std::string out;
  for (auto& statement : statements)
  {
    if (!out.empty()) out += " ";
    out += printer.print(statement.get());
  }
  return out;
}

// The only statement parsed, as a T, or nullptr if there isn't exactly one statement of that type.
template <typename T> T* onlyStmt(const std::vector<std::unique_ptr<jm::Stmt>>& statements)
{
  return statements.size() == 1 ? dynamic_cast<T*>(statements[0].get()) : nullptr;
}

using Case = std::pair<std::string_view, std::string_view>; // source, expected S-expression

void expectAll(std::initializer_list<Case> cases)
{
  for (const auto& [source, expected] : cases)
  {
    SCOPED_TRACE(source);
    EXPECT_EQ(parseExpr(source), expected);
  }
}

void expectAllStmts(std::initializer_list<Case> cases)
{
  for (const auto& [source, expected] : cases)
  {
    SCOPED_TRACE(source);
    EXPECT_EQ(parseStmts(source), expected);
  }
}
} // namespace

// ---------------------------------------------------------------------------
// Primary expressions
// ---------------------------------------------------------------------------

TEST(PrimaryExprTest, Identifier)
{
  auto statements = parse("x;");
  auto* name = dynamic_cast<jm::NameExpr*>(onlyExpr(statements));

  ASSERT_NE(name, nullptr);
  EXPECT_EQ(name->name.type, TokenType::Identifier);
  EXPECT_EQ(name->name.lexeme, "x");
}

TEST(PrimaryExprTest, IntLiteral)
{
  auto statements = parse("42;");
  auto* literal = dynamic_cast<jm::LiteralExpr*>(onlyExpr(statements));

  ASSERT_NE(literal, nullptr);
  EXPECT_EQ(literal->value.type, TokenType::IntLiteral);
  EXPECT_EQ(literal->value.lexeme, "42");
}

TEST(PrimaryExprTest, FloatLiteral)
{
  auto statements = parse("3.14;");
  auto* literal = dynamic_cast<jm::LiteralExpr*>(onlyExpr(statements));

  ASSERT_NE(literal, nullptr);
  EXPECT_EQ(literal->value.type, TokenType::FloatLiteral);
  EXPECT_EQ(literal->value.lexeme, "3.14");
}

TEST(PrimaryExprTest, CharLiteral)
{
  auto statements = parse("'a';");
  auto* literal = dynamic_cast<jm::LiteralExpr*>(onlyExpr(statements));

  ASSERT_NE(literal, nullptr);
  EXPECT_EQ(literal->value.type, TokenType::CharLiteral);
  EXPECT_EQ(literal->value.lexeme, "'a'");
}

TEST(PrimaryExprTest, StringLiteral)
{
  auto statements = parse("\"hi\";");
  auto* literal = dynamic_cast<jm::LiteralExpr*>(onlyExpr(statements));

  ASSERT_NE(literal, nullptr);
  EXPECT_EQ(literal->value.type, TokenType::StringLiteral);
  EXPECT_EQ(literal->value.lexeme, "\"hi\"");
}

TEST(PrimaryExprTest, ParenthesesDontAddANode)
{
  auto statements = parse("(x);");
  auto* name = dynamic_cast<jm::NameExpr*>(onlyExpr(statements));

  ASSERT_NE(name, nullptr);
  EXPECT_EQ(name->name.lexeme, "x");
}

TEST(PrimaryExprTest, NestedParentheses)
{
  EXPECT_EQ(parseExpr("((42));"), "42");
}

TEST(PrimaryExprTest, ParenthesesOverridePrecedence)
{
  expectAll({
      {"(1 + 2) * 3;", "(* (+ 1 2) 3)"},
      {"a * (b + c);", "(* a (+ b c))"},
      {"(a || b) && c;", "(&& (|| a b) c)"},
      {"a - (b - c);", "(- a (- b c))"},
  });
}

TEST(PrimaryExprTest, ParenthesesHoldAFullExpression)
{
  expectAll({
      {"(a = 1);", "(= a 1)"},
      {"(a, b);", "(, a b)"},
      {"(a ? b : c) + 1;", "(+ (?: a b c) 1)"},
  });
}

// ---------------------------------------------------------------------------
// Binary expressions
// ---------------------------------------------------------------------------

TEST(BinaryExprTest, EveryOperator)
{
  expectAll({
      {"a * b;", "(* a b)"},
      {"a / b;", "(/ a b)"},
      {"a % b;", "(% a b)"},
      {"a + b;", "(+ a b)"},
      {"a - b;", "(- a b)"},
      {"a << b;", "(<< a b)"},
      {"a >> b;", "(>> a b)"},
      {"a < b;", "(< a b)"},
      {"a > b;", "(> a b)"},
      {"a <= b;", "(<= a b)"},
      {"a >= b;", "(>= a b)"},
      {"a == b;", "(== a b)"},
      {"a != b;", "(!= a b)"},
      {"a & b;", "(& a b)"},
      {"a ^ b;", "(^ a b)"},
      {"a | b;", "(| a b)"},
      {"a && b;", "(&& a b)"},
      {"a || b;", "(|| a b)"},
  });
}

TEST(BinaryExprTest, MultiplicationBindsTighterThanAddition)
{
  expectAll({
      {"1 + 2 * 3;", "(+ 1 (* 2 3))"},
      {"1 * 2 + 3;", "(+ (* 1 2) 3)"},
  });
}

// Each level against the one directly above it, with the tighter operator on either side.
TEST(BinaryExprTest, PrecedenceLadder)
{
  expectAll({
      {"a || b && c;", "(|| a (&& b c))"}, {"a && b || c;", "(|| (&& a b) c)"},
      {"a && b | c;", "(&& a (| b c))"},   {"a | b && c;", "(&& (| a b) c)"},
      {"a | b ^ c;", "(| a (^ b c))"},     {"a ^ b | c;", "(| (^ a b) c)"},
      {"a ^ b & c;", "(^ a (& b c))"},     {"a & b ^ c;", "(^ (& a b) c)"},
      {"a & b == c;", "(& a (== b c))"},   {"a == b & c;", "(& (== a b) c)"},
      {"a == b < c;", "(== a (< b c))"},   {"a < b == c;", "(== (< a b) c)"},
      {"a != b >= c;", "(!= a (>= b c))"}, {"a > b != c;", "(!= (> a b) c)"},
      {"a < b << c;", "(< a (<< b c))"},   {"a << b < c;", "(< (<< a b) c)"},
      {"a << b + c;", "(<< a (+ b c))"},   {"a + b << c;", "(<< (+ a b) c)"},
      {"a >> b - c;", "(>> a (- b c))"},   {"a - b >> c;", "(>> (- a b) c)"},
      {"a + b * c;", "(+ a (* b c))"},     {"a * b + c;", "(+ (* a b) c)"},
      {"a - b % c;", "(- a (% b c))"},     {"a / b - c;", "(- (/ a b) c)"},
  });
}

TEST(BinaryExprTest, EveryLevelInOneExpression)
{
  EXPECT_EQ(parseExpr("a || b && c | d ^ e & f == g < h << i + j * k;"),
            "(|| a (&& b (| c (^ d (& e (== f (< g (<< h (+ i (* j k))))))))))");
}

TEST(BinaryExprTest, LeftAssociative)
{
  expectAll({
      {"a - b - c;", "(- (- a b) c)"},
      {"a / b / c;", "(/ (/ a b) c)"},
      {"a << b << c;", "(<< (<< a b) c)"},
      {"a < b < c;", "(< (< a b) c)"},
      {"a == b == c;", "(== (== a b) c)"},
      {"a & b & c;", "(& (& a b) c)"},
      {"a ^ b ^ c;", "(^ (^ a b) c)"},
      {"a | b | c;", "(| (| a b) c)"},
      {"a && b && c;", "(&& (&& a b) c)"},
      {"a || b || c;", "(|| (|| a b) c)"},
  });
}

TEST(BinaryExprTest, SameLevelOperatorsGroupLeftToRight)
{
  expectAll({
      {"a + b - c + d;", "(+ (- (+ a b) c) d)"},
      {"a * b / c % d;", "(% (/ (* a b) c) d)"},
      {"a < b > c <= d;", "(<= (> (< a b) c) d)"},
      {"a == b != c;", "(!= (== a b) c)"},
  });
}

// ---------------------------------------------------------------------------
// Unary expressions
// ---------------------------------------------------------------------------

TEST(UnaryExprTest, EveryOperator)
{
  expectAll({
      {"-x;", "(- x)"},
      {"+x;", "(+ x)"},
      {"!x;", "(! x)"},
      {"~x;", "(~ x)"},
      {"*p;", "(* p)"},
      {"&x;", "(& x)"},
      {"++x;", "(++ x)"},
      {"--x;", "(-- x)"},
  });
}

TEST(UnaryExprTest, Nested)
{
  expectAll({
      {"!!x;", "(! (! x))"},
      {"- -x;", "(- (- x))"},
      {"**pp;", "(* (* pp))"},
      {"*&x;", "(* (& x))"},
      {"-~x;", "(- (~ x))"},
      {"++*p;", "(++ (* p))"},
  });
}

TEST(UnaryExprTest, BindsTighterThanBinary)
{
  expectAll({
      {"-a * b;", "(* (- a) b)"},
      {"*p + 1;", "(+ (* p) 1)"},
      {"a - -b;", "(- a (- b))"},
      {"a * *p;", "(* a (* p))"},
      {"!a && b;", "(&& (! a) b)"},
      {"&a == b;", "(== (& a) b)"},
  });
}

TEST(UnaryExprTest, SizeofExpression)
{
  expectAll({
      {"sizeof x;", "(sizeof x)"},
      {"sizeof -x;", "(sizeof (- x))"},
      {"sizeof a[0];", "(sizeof (index a 0))"},
      {"sizeof x + 1;", "(+ (sizeof x) 1)"},
  });
}

// ---------------------------------------------------------------------------
// Postfix expressions
// ---------------------------------------------------------------------------

TEST(PostfixExprTest, CallWithNoArguments)
{
  EXPECT_EQ(parseExpr("f();"), "(call f)");
}

TEST(PostfixExprTest, CallWithArguments)
{
  expectAll({
      {"f(a);", "(call f a)"},
      {"f(a, b, c);", "(call f a b c)"},
      {"f(a + b, g(c));", "(call f (+ a b) (call g c))"},
  });
}

// Commas between arguments separate them; they aren't the comma operator.
TEST(PostfixExprTest, ArgumentsAreAssignmentExpressions)
{
  expectAll({
      {"f(a = 1, b ? c : d);", "(call f (= a 1) (?: b c d))"},
      {"f((a, b));", "(call f (, a b))"},
      {"f((a, b), c);", "(call f (, a b) c)"},
  });
}

TEST(PostfixExprTest, ChainedCalls)
{
  EXPECT_EQ(parseExpr("f(a)(b);"), "(call (call f a) b)");
}

TEST(PostfixExprTest, Index)
{
  expectAll({
      {"a[i];", "(index a i)"},
      {"a[i + 1];", "(index a (+ i 1))"},
      {"a[i][j];", "(index (index a i) j)"},
      {"a[b[i]];", "(index a (index b i))"},
      {"a[i, j];", "(index a (, i j))"},
  });
}

TEST(PostfixExprTest, Field)
{
  expectAll({
      {"p.x;", "(. p x)"},
      {"p->x;", "(-> p x)"},
      {"a.b.c;", "(. (. a b) c)"},
      {"p->next->value;", "(-> (-> p next) value)"},
      {"p->pos.x;", "(. (-> p pos) x)"},
  });
}

TEST(PostfixExprTest, MixedChain)
{
  expectAll({
      {"f(x)[0].y;", "(. (index (call f x) 0) y)"},
      {"obj.method(1);", "(call (. obj method) 1)"},
      {"p->items[i];", "(index (-> p items) i)"},
      {"table[i](x);", "(call (index table i) x)"},
  });
}

TEST(PostfixExprTest, BindsTighterThanPrefix)
{
  expectAll({
      {"-a[0];", "(- (index a 0))"},
      {"*p.x;", "(* (. p x))"},
      {"&s->field;", "(& (-> s field))"},
      {"!f(x);", "(! (call f x))"},
  });
}

TEST(PostfixExprTest, BindsTighterThanBinary)
{
  EXPECT_EQ(parseExpr("a + b[0] * c.d;"), "(+ a (* (index b 0) (. c d)))");
}

// ---------------------------------------------------------------------------
// Conditional expressions
// ---------------------------------------------------------------------------

TEST(ConditionalExprTest, Simple)
{
  EXPECT_EQ(parseExpr("a ? b : c;"), "(?: a b c)");
}

TEST(ConditionalExprTest, RightAssociative)
{
  EXPECT_EQ(parseExpr("a ? b : c ? d : e;"), "(?: a b (?: c d e))");
}

TEST(ConditionalExprTest, NestedInTheMiddle)
{
  EXPECT_EQ(parseExpr("a ? b ? c : d : e;"), "(?: a (?: b c d) e)");
}

TEST(ConditionalExprTest, BindsLooserThanLogicalOr)
{
  expectAll({
      {"a || b ? c : d;", "(?: (|| a b) c d)"},
      {"a ? b + 1 : c * 2;", "(?: a (+ b 1) (* c 2))"},
  });
}

// The middle operand is a full expression, so it can hold a comma or an assignment.
TEST(ConditionalExprTest, MiddleIsAFullExpression)
{
  expectAll({
      {"a ? b, c : d;", "(?: a (, b c) d)"},
      {"a ? x = 1 : y;", "(?: a (= x 1) y)"},
  });
}

// ---------------------------------------------------------------------------
// Assignment expressions
// ---------------------------------------------------------------------------

TEST(AssignExprTest, EveryOperator)
{
  expectAll({
      {"a = 1;", "(= a 1)"},
      {"a += 1;", "(+= a 1)"},
      {"a -= 1;", "(-= a 1)"},
      {"a *= 1;", "(*= a 1)"},
      {"a /= 1;", "(/= a 1)"},
      {"a %= 1;", "(%= a 1)"},
      {"a &= 1;", "(&= a 1)"},
      {"a |= 1;", "(|= a 1)"},
      {"a ^= 1;", "(^= a 1)"},
      {"a <<= 1;", "(<<= a 1)"},
      {"a >>= 1;", "(>>= a 1)"},
  });
}

TEST(AssignExprTest, RightAssociative)
{
  expectAll({
      {"a = b = c;", "(= a (= b c))"},
      {"a = b = c = d;", "(= a (= b (= c d)))"},
      {"a += b -= c;", "(+= a (-= b c))"},
  });
}

TEST(AssignExprTest, ValueBindsTighterThanAssignment)
{
  expectAll({
      {"a = b + c * d;", "(= a (+ b (* c d)))"},
      {"a = b || c;", "(= a (|| b c))"},
      {"a = b ? c : d;", "(= a (?: b c d))"},
  });
}

TEST(AssignExprTest, Targets)
{
  expectAll({
      {"a[i] = 1;", "(= (index a i) 1)"},
      {"*p = 0;", "(= (* p) 0)"},
      {"p->x = 1;", "(= (-> p x) 1)"},
      {"s.x += 2;", "(+= (. s x) 2)"},
      {"(a) = 1;", "(= a 1)"},
  });
}

// Enable once assignmentExpression() checks that its target can be assigned to.
TEST(AssignExprTest, DISABLED_RejectsTargetThatIsNotAssignable)
{
  ASSERT_FALSE(reportsError("x = 1;"));

  EXPECT_TRUE(reportsError("1 = x;"));
  EXPECT_TRUE(reportsError("a + b = c;"));
  EXPECT_TRUE(reportsError("f() = 1;"));
}

// ---------------------------------------------------------------------------
// Comma expressions
// ---------------------------------------------------------------------------

TEST(CommaExprTest, TwoExpressions)
{
  EXPECT_EQ(parseExpr("a, b;"), "(, a b)");
}

TEST(CommaExprTest, IsFlatNotNested)
{
  EXPECT_EQ(parseExpr("a, b, c;"), "(, a b c)");
}

TEST(CommaExprTest, BindsLoosestOfAll)
{
  expectAll({
      {"a = 1, b = 2;", "(, (= a 1) (= b 2))"},
      {"a ? b : c, d;", "(, (?: a b c) d)"},
      {"a || b, c && d;", "(, (|| a b) (&& c d))"},
  });
}

TEST(CommaExprTest, NoCommaExprWithoutAComma)
{
  auto withComma = parse("a = 1, b;");
  ASSERT_NE(dynamic_cast<jm::CommaExpr*>(onlyExpr(withComma)), nullptr);

  auto withoutComma = parse("a = 1;");
  jm::Expr* expr = onlyExpr(withoutComma);
  ASSERT_NE(expr, nullptr);
  EXPECT_EQ(dynamic_cast<jm::CommaExpr*>(expr), nullptr);
  EXPECT_NE(dynamic_cast<jm::AssignExpr*>(expr), nullptr);
}

// ---------------------------------------------------------------------------
// Expression statements
// ---------------------------------------------------------------------------

TEST(ExpressionStmtTest, MultipleStatements)
{
  auto statements = parse("a; b = 1; f(x);");
  ASSERT_EQ(statements.size(), 3);

  std::vector<std::string> printed;
  for (auto& statement : statements)
  {
    auto* expressionStmt = dynamic_cast<jm::ExpressionStmt*>(statement.get());
    ASSERT_NE(expressionStmt, nullptr);
    printed.push_back(AstPrinter().print(expressionStmt->expr.get()));
  }
  EXPECT_EQ(printed, (std::vector<std::string>{"a", "(= b 1)", "(call f x)"}));
}

// ---------------------------------------------------------------------------
// Errors
// Each test first checks that the fixed-up input parses cleanly, so the error really comes from
// the one thing that's broken.
// ---------------------------------------------------------------------------

TEST(ParseErrorTest, MissingSemicolon)
{
  ASSERT_FALSE(reportsError("a + b;"));
  EXPECT_TRUE(reportsError("a + b"));
}

TEST(ParseErrorTest, MissingOperand)
{
  ASSERT_FALSE(reportsError("a + b;"));
  EXPECT_TRUE(reportsError("a + ;"));
  EXPECT_TRUE(reportsError("a = ;"));
  EXPECT_TRUE(reportsError("-;"));
}

TEST(ParseErrorTest, UnexpectedToken)
{
  EXPECT_TRUE(reportsError(");"));
  EXPECT_TRUE(reportsError("];"));
}

TEST(ParseErrorTest, MissingCloseParen)
{
  ASSERT_FALSE(reportsError("(a + b);"));
  EXPECT_TRUE(reportsError("(a + b;"));
}

TEST(ParseErrorTest, MissingColonInConditional)
{
  ASSERT_FALSE(reportsError("a ? b : c;"));
  EXPECT_TRUE(reportsError("a ? b;"));
}

TEST(ParseErrorTest, MissingCloseBracket)
{
  ASSERT_FALSE(reportsError("a[i];"));
  EXPECT_TRUE(reportsError("a[i;"));
}

TEST(ParseErrorTest, UnclosedCall)
{
  ASSERT_FALSE(reportsError("f(a, b);"));
  EXPECT_TRUE(reportsError("f(a, b;"));
}

TEST(ParseErrorTest, TrailingCommaInCall)
{
  ASSERT_FALSE(reportsError("f(a);"));
  EXPECT_TRUE(reportsError("f(a,);"));
}

TEST(ParseErrorTest, MissingFieldName)
{
  ASSERT_FALSE(reportsError("p.x;"));
  ASSERT_FALSE(reportsError("p->x;"));

  EXPECT_TRUE(reportsError("p.;"));
  EXPECT_TRUE(reportsError("p->;"));
}

TEST(ParseErrorTest, ReportsTheLineItHappenedOn)
{
  std::string firstLine = parseErrors("(b;");
  ASSERT_NE(firstLine.find("line 1"), std::string::npos);

  std::string secondLine = parseErrors("a;\n(b;");
  EXPECT_EQ(secondLine.find("line 1"), std::string::npos);
  EXPECT_NE(secondLine.find("line 2"), std::string::npos);
}

TEST(ParseErrorTest, RecoversAtTheNextStatement)
{
  testing::internal::CaptureStderr();
  auto statements = parse("a + ; b = 1;");
  std::string errors = testing::internal::GetCapturedStderr();

  EXPECT_NE(errors.find("ParseError"), std::string::npos);
  ASSERT_EQ(statements.size(), 1);
  auto* statement = dynamic_cast<jm::ExpressionStmt*>(statements[0].get());
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(AstPrinter().print(statement->expr.get()), "(= b 1)");
}

// ---------------------------------------------------------------------------
// Statements
// ---------------------------------------------------------------------------

TEST(ExpressionStmtTest, EmptyStatement)
{
  auto nonEmpty = parse("x;");
  auto* withExpr = onlyStmt<jm::ExpressionStmt>(nonEmpty);
  ASSERT_NE(withExpr, nullptr);
  ASSERT_NE(withExpr->expr, nullptr);

  auto empty = parse(";");
  auto* statement = onlyStmt<jm::ExpressionStmt>(empty);
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(statement->expr, nullptr);
  EXPECT_EQ(parseStmts("; ;"), "; ;");
}

TEST(BlockStmtTest, Blocks)
{
  expectAllStmts({
      {"{}", "(block)"},
      {"{ a; b = 1; }", "(block a; (= b 1);)"},
      {"{ { a; } b; }", "(block (block a;) b;)"},
      {"{ ; }", "(block ;)"},
      {"{ a; } b;", "(block a;) b;"},
  });
}

TEST(IfStmtTest, IfAndElse)
{
  expectAllStmts({
      {"if (a) b;", "(if a b;)"},
      {"if (a) b; else c;", "(if a b; c;)"},
      {"if (a) { b; } else { c; }", "(if a (block b;) (block c;))"},
      {"if (a = f(), a) b;", "(if (, (= a (call f)) a) b;)"},
  });
}

TEST(IfStmtTest, ElseIfChainNests)
{
  EXPECT_EQ(parseStmts("if (a) b; else if (c) d; else e;"), "(if a b; (if c d; e;))");
}

TEST(IfStmtTest, DanglingElseGoesToTheNearestIf)
{
  EXPECT_EQ(parseStmts("if (a) if (b) c; else d;"), "(if a (if b c; d;))");
}

TEST(IfStmtTest, ElseBranchIsNullWithoutElse)
{
  auto withElse = parse("if (a) b; else c;");
  auto* hasElse = onlyStmt<jm::IfStmt>(withElse);
  ASSERT_NE(hasElse, nullptr);
  ASSERT_NE(hasElse->elseBranch, nullptr);

  auto withoutElse = parse("if (a) b;");
  auto* noElse = onlyStmt<jm::IfStmt>(withoutElse);
  ASSERT_NE(noElse, nullptr);
  EXPECT_EQ(noElse->elseBranch, nullptr);
}

TEST(WhileStmtTest, Loops)
{
  expectAllStmts({
      {"while (a) b;", "(while a b;)"},
      {"while (i < n) { i++; }", "(while (< i n) (block (++ i);))"},
      {"while (x) ;", "(while x ;)"},
  });
}

TEST(DoWhileStmtTest, Loops)
{
  expectAllStmts({
      {"do a; while (b);", "(do a; b)"},
      {"do { i++; } while (i < 10);", "(do (block (++ i);) (< i 10))"},
      {"do ; while (x);", "(do ; x)"},
  });
}

TEST(ForStmtTest, AllClauses)
{
  EXPECT_EQ(parseStmts("for (i = 0; i < n; i++) s += i;"),
            "(for (= i 0); (< i n) (++ i) (+= s i);)");
}

TEST(ForStmtTest, EveryClauseIsOptional)
{
  expectAllStmts({
      {"for (;;) x;", "(for _ _ _ x;)"},
      {"for (i = 0;;) x;", "(for (= i 0); _ _ x;)"},
      {"for (; i < n;) x;", "(for _ (< i n) _ x;)"},
      {"for (;; i++) x;", "(for _ _ (++ i) x;)"},
  });
}

TEST(ForStmtTest, CommasInClauses)
{
  EXPECT_EQ(parseStmts("for (i = 0, j = n; i < j; i++, j--) swap(i, j);"),
            "(for (, (= i 0) (= j n)); (< i j) (, (++ i) (-- j)) (call swap i j);)");
}

TEST(ForStmtTest, BlockBody)
{
  EXPECT_EQ(parseStmts("for (;;) { break; }"), "(for _ _ _ (block (break)))");
}

TEST(ForStmtTest, InitIsAnExpressionStatement)
{
  auto statements = parse("for (i = 0; i < n; i++) x;");
  auto* loop = onlyStmt<jm::ForStmt>(statements);
  ASSERT_NE(loop, nullptr);
  EXPECT_NE(dynamic_cast<jm::ExpressionStmt*>(loop->init.get()), nullptr);
}

TEST(ReturnStmtTest, Values)
{
  expectAllStmts({
      {"return;", "(return)"},
      {"return x;", "(return x)"},
      {"return a + b * c;", "(return (+ a (* b c)))"},
      {"return a, b;", "(return (, a b))"},
  });
}

TEST(ReturnStmtTest, KeepsItsKeyword)
{
  auto statements = parse("\nreturn x;");
  auto* statement = onlyStmt<jm::ReturnStmt>(statements);
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(statement->keyword.type, TokenType::Return);
  EXPECT_EQ(statement->keyword.line, 2);
}

TEST(JumpStmtTest, BreakAndContinue)
{
  expectAllStmts({
      {"break;", "(break)"},
      {"continue;", "(continue)"},
  });
}

TEST(JumpStmtTest, BreakKeepsItsKeyword)
{
  auto statements = parse("\n\nbreak;");
  auto* statement = onlyStmt<jm::BreakStmt>(statements);
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(statement->keyword.type, TokenType::Break);
  EXPECT_EQ(statement->keyword.lexeme, "break");
  EXPECT_EQ(statement->keyword.line, 3);
}

TEST(JumpStmtTest, ContinueKeepsItsKeyword)
{
  auto statements = parse("\n\ncontinue;");
  auto* statement = onlyStmt<jm::ContinueStmt>(statements);
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(statement->keyword.type, TokenType::Continue);
  EXPECT_EQ(statement->keyword.lexeme, "continue");
  EXPECT_EQ(statement->keyword.line, 3);
}

TEST(StatementTest, Nesting)
{
  expectAllStmts({
      {"while (1) { if (x) break; else continue; }", "(while 1 (block (if x (break) (continue))))"},
      {"if (n < 0) { return -1; } else if (n == 0) { return 0; }",
       "(if (< n 0) (block (return (- 1))) (if (== n 0) (block (return 0))))"},
      {"for (i = 0; i < n; i++) { if (i % 2 == 0) { continue; } result += i; }",
       "(for (= i 0); (< i n) (++ i) (block (if (== (% i 2) 0) (block (continue))) (+= result "
       "i);))"},
  });
}

TEST(StatementErrorTest, UnclosedBlock)
{
  ASSERT_FALSE(reportsError("{ a; }"));
  EXPECT_TRUE(reportsError("{ a;"));
}

TEST(StatementErrorTest, IfParentheses)
{
  ASSERT_FALSE(reportsError("if (a) b;"));
  EXPECT_TRUE(reportsError("if a) b;"));
  EXPECT_TRUE(reportsError("if (a b;"));
}

TEST(StatementErrorTest, MissingBody)
{
  ASSERT_FALSE(reportsError("if (a) ;"));
  EXPECT_TRUE(reportsError("if (a)"));
  EXPECT_TRUE(reportsError("while (a)"));
}

TEST(StatementErrorTest, WhileParentheses)
{
  ASSERT_FALSE(reportsError("while (a) b;"));
  EXPECT_TRUE(reportsError("while a) b;"));
  EXPECT_TRUE(reportsError("while (a b;"));
}

TEST(StatementErrorTest, DoWhile)
{
  ASSERT_FALSE(reportsError("do a; while (b);"));
  EXPECT_TRUE(reportsError("do a; (b);"));
  EXPECT_TRUE(reportsError("do a; while b);"));
  EXPECT_TRUE(reportsError("do a; while (b;"));
  EXPECT_TRUE(reportsError("do a; while (b)"));
}

TEST(StatementErrorTest, ForClauses)
{
  ASSERT_FALSE(reportsError("for (i = 0; i < n; i++) x;"));
  EXPECT_TRUE(reportsError("for i = 0; i < n; i++) x;"));
  EXPECT_TRUE(reportsError("for (i = 0 i < n; i++) x;"));
  EXPECT_TRUE(reportsError("for (i = 0; i < n i++) x;"));
  EXPECT_TRUE(reportsError("for (i = 0; i < n; i++ x;"));
}

TEST(StatementErrorTest, MissingSemicolonAfterJump)
{
  ASSERT_FALSE(reportsError("return x; break; continue;"));
  EXPECT_TRUE(reportsError("return x"));
  EXPECT_TRUE(reportsError("break"));
  EXPECT_TRUE(reportsError("continue"));
}

TEST(StatementErrorTest, RecoversAtTheNextKeyword)
{
  testing::internal::CaptureStderr();
  auto statements = parse("if (a b) return 1;");
  std::string errors = testing::internal::GetCapturedStderr();

  EXPECT_NE(errors.find("ParseError"), std::string::npos);
  auto* statement = onlyStmt<jm::ReturnStmt>(statements);
  ASSERT_NE(statement, nullptr);
  EXPECT_EQ(AstPrinter().print(statement), "(return 1)");
}
