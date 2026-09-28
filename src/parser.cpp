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
#include "statements/stmt.hpp"
#include "statements/struct_decl.hpp"
#include "statements/var_decl_stmt.hpp"
#include "statements/while_stmt.hpp"
#include "token.hpp"
#include "type.hpp"
#include "visitor.hpp"
#include <iostream>
#include <memory>
#include <parser.hpp>
namespace jm
{
namespace
{
// Whether a token can start a type name, e.g. the `int` in `(int)x`.
bool isTypeKeyword(TokenType type)
{
  switch (type)
  {
    case TokenType::Void:
    case TokenType::Char:
    case TokenType::Short:
    case TokenType::Int:
    case TokenType::Long:
    case TokenType::Float:
    case TokenType::Double:
    case TokenType::Signed:
    case TokenType::Unsigned:
    case TokenType::Bool:
    case TokenType::Struct:
    case TokenType::Union:
    case TokenType::Enum:
    case TokenType::Const:
    case TokenType::Volatile: return true;
    default: return false;
  }
}
} // namespace

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
  std::vector<std::unique_ptr<Stmt>> statements;
  while (!isAtEnd())
  {
    try
    {
      statements.push_back(statement());
    }
    catch (ParseError& error)
    {
      std::cerr << "ParseError: " << error.what() << " at line " << error.line << "\n";
      sync();
    }
  }
  return statements;
}

std::unique_ptr<Stmt> Parser::statement()
{
  // statement ::= labeled-statement | compound-statement | expression-statement
  //             | selection-statement | iteration-statement | jump-statement
  //
  // labeled-statement:    case 1: x = 5;         myLabel: goto myLabel;
  // compound-statement:   { int x = 1; x++; }
  // expression-statement: x = 5;                 foo();
  // selection-statement:  if (x > 0) { ... }      switch (x) { ... }
  // iteration-statement:  while (x < 10) { ... }  for (i = 0; i < 10; i++) { ... }
  // jump-statement:       return 0;               break;  continue;  goto myLabel;

  if (match(TokenType::LBrace)) return blockStatement();
  if (match(TokenType::If)) return ifStatement();
  if (match(TokenType::While)) return whileStatement();
  if (match(TokenType::Do)) return doWhileStatement();
  if (match(TokenType::For)) return forStatement();
  if (match(TokenType::Return)) return returnStatement();
  if (match(TokenType::Break)) return breakStatement();
  if (match(TokenType::Continue)) return continueStatement();
  return expressionStatement();
}

std::unique_ptr<Stmt> Parser::blockStatement()
{
  // compound-statement ::= '{' (declaration | statement)* '}'
  std::vector<std::unique_ptr<Stmt>> stmts;
  while (!isAtEnd() && peek().type != TokenType::RBrace)
  {
    stmts.push_back(statement());
  }
  consume(TokenType::RBrace, "expected '}' after block");
  return std::make_unique<BlockStmt>(std::move(stmts));
}

std::unique_ptr<Stmt> Parser::ifStatement()
{
  // selection-statement ::= 'if' '(' expression ')' statement ('else' statement)?
  consume(TokenType::LParen, "expected '(' after 'if'");
  auto condition = expression();
  consume(TokenType::RParen, "expected ')' after condition");
  auto then_branch = statement();
  auto if_stmt = std::make_unique<IfStmt>(std::move(condition), std::move(then_branch), nullptr);
  if (match(TokenType::Else))
  {
    if_stmt->elseBranch = statement();
  }
  return if_stmt;
}

std::unique_ptr<Stmt> Parser::whileStatement()
{
  // iteration-statement ::= 'while' '(' expression ')' statement
  consume(TokenType::LParen, "expected '(' after 'while'");
  auto condition = expression();
  consume(TokenType::RParen, "expected ')' after condition");
  auto stmt = statement();
  return std::make_unique<WhileStmt>(std::move(condition), std::move(stmt));
}

std::unique_ptr<Stmt> Parser::doWhileStatement()
{
  // iteration-statement ::= 'do' statement 'while' '(' expression ')' ';'
  auto stmt = statement();
  consume(TokenType::While, "expected 'while' after do body");
  consume(TokenType::LParen, "expected '(' after 'while'");
  auto expr = expression();
  consume(TokenType::RParen, "expected ')' after condition");
  consume(TokenType::Semicolon, "expected ';' after do-while");
  return std::make_unique<DoWhileStmt>(std::move(stmt), std::move(expr));
}

std::unique_ptr<Stmt> Parser::forStatement()
{
  // iteration-statement ::= 'for' '(' expression? ';' expression? ';' expression? ')' statement
  consume(TokenType::LParen, "expected '(' after 'for'");
  std::unique_ptr<Stmt> init = match(TokenType::Semicolon) ? nullptr : expressionStatement();
  auto cond = peek().type == TokenType::Semicolon ? nullptr : expression();
  consume(TokenType::Semicolon, "expected ';' after for condition");
  auto update = peek().type == TokenType::RParen ? nullptr : expression();
  consume(TokenType::RParen, "expected ')' after for clauses");
  auto stmt = statement();
  return std::make_unique<ForStmt>(std::move(init), std::move(cond), std::move(update),
                                   std::move(stmt));
}

std::unique_ptr<Stmt> Parser::returnStatement()
{
  // jump-statement ::= 'return' expression? ';'
  Token keyword = previous();
  std::unique_ptr<Expr> expr = nullptr;
  if (peek().type != TokenType::Semicolon)
  {
    expr = expression();
  }
  consume(TokenType::Semicolon, "expected ';' after return");
  return std::make_unique<ReturnStmt>(keyword, std::move(expr));
}

std::unique_ptr<Stmt> Parser::breakStatement()
{
  // jump-statement ::= 'break' ';'
  Token keyword = previous();
  consume(TokenType::Semicolon, "expected ';' after break");
  return std::make_unique<BreakStmt>(keyword);
}

std::unique_ptr<Stmt> Parser::continueStatement()
{
  // jump-statement ::= 'continue' ';'
  Token keyword = previous();
  consume(TokenType::Semicolon, "expected ';' after continue");
  return std::make_unique<ContinueStmt>(keyword);
}

std::unique_ptr<Stmt> Parser::expressionStatement()
{
  // expression-statement ::= expression? ';'
  if (match(TokenType::Semicolon))
  {
    return std::make_unique<ExpressionStmt>(nullptr);
  }
  auto expr = expression();
  consume(TokenType::Semicolon, "expected ';' after expression");
  return std::make_unique<ExpressionStmt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::expression()
{
  // expression ::= assignment-expression (',' assignment-expression)*
  std::vector<std::unique_ptr<Expr>> expressions;
  expressions.push_back(assignmentExpression());
  while (match(TokenType::Comma))
  {
    expressions.push_back(assignmentExpression());
  }
  if (expressions.size() == 1) return std::move(expressions[0]);
  return std::make_unique<CommaExpr>(std::move(expressions));
}

std::unique_ptr<Expr> Parser::assignmentExpression()
{
  // assignment-expression ::= conditional-expression
  //                         | unary-expression assignment-operator assignment-expression

  auto conditional_expression = conditionalExpression();
  if (match(TokenType::Equal, TokenType::PlusEqual, TokenType::MinusEqual, TokenType::StarEqual,
            TokenType::SlashEqual, TokenType::PercentEqual, TokenType::AmpEqual,
            TokenType::PipeEqual, TokenType::CaretEqual, TokenType::LessLessEqual,
            TokenType::GreaterGreaterEqual))
  {
    Token prev = previous();
    return std::make_unique<AssignExpr>(std::move(conditional_expression), std::move(prev),
                                        std::move(assignmentExpression()));
  }
  return conditional_expression;
}

std::unique_ptr<Expr> Parser::conditionalExpression()
{
  // conditional-expression ::= logical-or-expression ('?' expression ':' conditional-expression)?

  auto logical_or_expression = logicalOrExpression();
  if (match(TokenType::Question))
  {
    auto expr = expression();
    consume(TokenType::Colon, "expected ':' in conditional expression");
    auto conditional_expression = conditionalExpression();
    return std::make_unique<ConditionalExpr>(std::move(logical_or_expression), std::move(expr),
                                             std::move(conditional_expression));
  }
  return logical_or_expression;
}

std::unique_ptr<Expr> Parser::logicalOrExpression()
{
  // logical-or-expression ::= logical-and-expression ('||' logical-and-expression)*
  auto expr = logicalAndExpression();
  while (match(TokenType::OrOr))
  {
    Token op = previous();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, logicalAndExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::logicalAndExpression()
{
  // logical-and-expression ::= inclusive-or-expression ('&&' inclusive-or-expression)*

  auto expr = inclusiveOrExpression();
  while (match(TokenType::AndAnd))
  {
    Token op = previous();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, inclusiveOrExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::inclusiveOrExpression()
{
  // inclusive-or-expression ::= exclusive-or-expression ('|' exclusive-or-expression)*
  auto expr = exclusiveOrExpression();
  while (match(TokenType::Pipe))
  {
    Token op = previous();
    expr = std::make_unique<BinaryExpr>(std::move(expr), op, exclusiveOrExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::exclusiveOrExpression()
{
  // exclusive-or-expression ::= and-expression ('^' and-expression)*
  auto expr = andExpression();
  while (match(TokenType::Caret))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, andExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::andExpression()
{
  // and-expression ::= equality-expression ('&' equality-expression)*
  auto expr = equalityExpression();
  while (match(TokenType::Amp))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, equalityExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::equalityExpression()
{
  // equality-expression ::= relational-expression (('==' | '!=') relational-expression)*
  auto expr = relationalExpression();
  while (match(TokenType::EqualEqual, TokenType::NotEqual))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, relationalExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::relationalExpression()
{
  // relational-expression ::= shift-expression (('<' | '>' | '<=' | '>=') shift-expression)*
  auto expr = shiftExpression();
  while (match(TokenType::Less, TokenType::LessEqual, TokenType::Greater, TokenType::GreaterEqual))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, shiftExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::shiftExpression()
{
  // shift-expression ::= additive-expression (('<<' | '>>') additive-expression)*
  auto expr = additiveExpression();
  while (match(TokenType::LessLess, TokenType::GreaterGreater))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, additiveExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::additiveExpression()
{
  // additive-expression ::= multiplicative-expression (('+' | '-') multiplicative-expression)*
  auto expr = multiplicativeExpression();
  while (match(TokenType::Plus, TokenType::Minus))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, multiplicativeExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::multiplicativeExpression()
{
  // multiplicative-expression ::= cast-expression (('*' | '/' | '%') cast-expression)*
  //
  auto expr = castExpression();
  while (match(TokenType::Star, TokenType::Slash, TokenType::Percent))
  {
    Token op = previous();
    expr = make_unique<BinaryExpr>(std::move(expr), op, castExpression());
  }
  return expr;
}

std::unique_ptr<Expr> Parser::castExpression()
{
  // cast-expression ::= unary-expression | '(' type-name ')' cast-expression
  if (check(TokenType::LParen) && isTypeKeyword(peekNext().type))
  {
    advance();
    Type type{advance()};
    while (match(TokenType::Star)) type.pointerDepth++;
    consume(TokenType::RParen, "expected ')' after type in cast");
    auto operand = castExpression();
    return std::make_unique<CastExpr>(type, std::move(operand));
  }
  return unaryExpression();
}

std::unique_ptr<Expr> Parser::unaryExpression()
{
  // unary-expression ::= postfix-expression
  //                    | ('++' | '--') unary-expression
  //                    | unary-operator cast-expression
  //                    | 'sizeof' (unary-expression | '(' type-name ')')

  if (match(TokenType::PlusPlus, TokenType::MinusMinus))
  {
    Token op = previous();
    return std::make_unique<UnaryExpr>(op, unaryExpression());
  }
  if (match(TokenType::Sizeof))
  {
    if (check(TokenType::LParen) && isTypeKeyword(peekNext().type))
    {
      advance();
      Type type{advance()};
      while (match(TokenType::Star)) type.pointerDepth++;
      consume(TokenType::RParen, "expected ')' after type in sizeof");
      return std::make_unique<SizeofExpr>(type);
    }
    return std::make_unique<SizeofExpr>(unaryExpression());
  }
  if (match(TokenType::Amp, TokenType::Star, TokenType::Plus, TokenType::Minus, TokenType::Tilde,
            TokenType::Not))
  {
    Token op = previous();
    return std::make_unique<UnaryExpr>(op, castExpression());
  }
  return postfixExpression();
}

std::unique_ptr<Expr> Parser::postfixExpression()
{
  // postfix-expression ::= primary-expression
  //                      | postfix-expression '[' expression ']'
  //                      | postfix-expression '(' argument-expression-list? ')'
  //                      | postfix-expression '.' identifier
  //                      | postfix-expression '->' identifier
  //                      | postfix-expression ('++' | '--')

  auto expr = primaryExpression();
  bool done = false;
  while (!done)
  {
    if (match(TokenType::LBracket))
    {
      auto innerExpr = expression();
      consume(TokenType::RBracket, "expected ']' after index");
      expr = std::make_unique<IndexExpr>(std::move(expr), std::move(innerExpr));
    }
    else if (match(TokenType::LParen))
    {
      std::vector<std::unique_ptr<Expr>> innerExpressions;
      if (!check(TokenType::RParen))
      {
        innerExpressions.push_back(assignmentExpression());
        while (match(TokenType::Comma))
        {
          innerExpressions.push_back(assignmentExpression());
        };
      }
      Token paren = consume(TokenType::RParen, "expected ')' after arguments");
      expr = std::make_unique<CallExpr>(std::move(expr), paren, std::move(innerExpressions));
    }
    else if (match(TokenType::Dot, TokenType::Arrow))
    {
      Token op = previous();
      Token field = consume(TokenType::Identifier, "expected field name");
      expr = std::make_unique<FieldExpr>(std::move(expr), op, field);
    }
    else if (match(TokenType::PlusPlus, TokenType::MinusMinus))
    {
      Token op = previous();
      expr = std::make_unique<UnaryExpr>(op, std::move(expr));
    }
    else
    {
      done = true;
    }
  }
  return expr;
}

std::unique_ptr<Expr> Parser::primaryExpression()
{
  // primary-expression ::= identifier | constant | string-literal | '(' expression ')'

  Token token = peek();
  if (match(TokenType::Identifier))
  {
    return std::make_unique<NameExpr>(std::move(token));
  }
  if (match(TokenType::IntLiteral, TokenType::FloatLiteral, TokenType::CharLiteral,
            TokenType::StringLiteral))
  {
    return std::make_unique<LiteralExpr>(std::move(token));
  }
  if (match(TokenType::LParen))
  {
    auto expr = expression();
    consume(TokenType::RParen, "expected ')' after expression");
    return expr;
  }
  throw ParseError("expected expression", peek().line);
}

const Token& Parser::advance()
{
  const Token& token = peek();
  if (!isAtEnd()) pos_++;
  return token;
}

const Token& Parser::peek()
{
  return tokens_[pos_];
}

const Token& Parser::peekNext()
{
  return pos_ + 1 >= tokens_.size() ? tokens_.back() : tokens_[pos_ + 1];
}

const Token& Parser::previous()
{
  return tokens_[pos_ - 1];
}

const Token& Parser::consume(TokenType type, const std::string& message)
{
  if (!check(type)) throw ParseError(message, peek().line);
  return advance();
}

bool Parser::check(TokenType type)
{
  return isAtEnd() ? false : peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types)
{
  for (TokenType type : types)
  {
    if (!check(type)) continue;
    advance();
    return true;
  }
  return false;
}

bool Parser::isAtEnd()
{
  return peek().type == TokenType::Eof;
}

void Parser::sync()
{
  advance();
  while (!isAtEnd())
  {
    if (previous().type == TokenType::Semicolon) return;
    switch (peek().type)
    {
      case TokenType::If:
      case TokenType::While:
      case TokenType::For:
      case TokenType::Return:
      case TokenType::Struct:
      case TokenType::Int:
      case TokenType::Void:
      case TokenType::Char:
      case TokenType::Float:
      case TokenType::Double: return;
      default: break;
    }
    advance();
  }
}

} // namespace jm
