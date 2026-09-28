#include "statements/stmt.hpp"
#include <iostream>
#include <parser.hpp>

namespace jm
{
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
  return nullptr;
}

std::unique_ptr<Stmt> Parser::ifStatement()
{
  // selection-statement ::= 'if' '(' expression ')' statement ('else' statement)?
  return nullptr;
}

std::unique_ptr<Stmt> Parser::whileStatement()
{
  // iteration-statement ::= 'while' '(' expression ')' statement
  return nullptr;
}

std::unique_ptr<Stmt> Parser::doWhileStatement()
{
  // iteration-statement ::= 'do' statement 'while' '(' expression ')' ';'
  return nullptr;
}

std::unique_ptr<Stmt> Parser::forStatement()
{
  // iteration-statement ::= 'for' '(' expression? ';' expression? ';' expression? ')' statement
  return nullptr;
}

std::unique_ptr<Stmt> Parser::returnStatement()
{
  // jump-statement ::= 'return' expression? ';'
  return nullptr;
}

std::unique_ptr<Stmt> Parser::breakStatement()
{
  // jump-statement ::= 'break' ';'
  return nullptr;
}

std::unique_ptr<Stmt> Parser::continueStatement()
{
  // jump-statement ::= 'continue' ';'
  return nullptr;
}

std::unique_ptr<Stmt> Parser::expressionStatement()
{
  // expression-statement ::= expression? ';'
  return nullptr;
}

std::unique_ptr<Expr> Parser::expression()
{
  // expression ::= assignment-expression (',' assignment-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::assignmentExpression()
{
  // assignment-expression ::= conditional-expression
  //                         | unary-expression assignment-operator assignment-expression
  return nullptr;
}

std::unique_ptr<Expr> Parser::conditionalExpression()
{
  // conditional-expression ::= logical-or-expression ('?' expression ':' conditional-expression)?
  return nullptr;
}

std::unique_ptr<Expr> Parser::logicalOrExpression()
{
  // logical-or-expression ::= logical-and-expression ('||' logical-and-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::logicalAndExpression()
{
  // logical-and-expression ::= inclusive-or-expression ('&&' inclusive-or-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::inclusiveOrExpression()
{
  // inclusive-or-expression ::= exclusive-or-expression ('|' exclusive-or-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::exclusiveOrExpression()
{
  // exclusive-or-expression ::= and-expression ('^' and-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::andExpression()
{
  // and-expression ::= equality-expression ('&' equality-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::equalityExpression()
{
  // equality-expression ::= relational-expression (('==' | '!=') relational-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::relationalExpression()
{
  // relational-expression ::= shift-expression (('<' | '>' | '<=' | '>=') shift-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::shiftExpression()
{
  // shift-expression ::= additive-expression (('<<' | '>>') additive-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::additiveExpression()
{
  // additive-expression ::= multiplicative-expression (('+' | '-') multiplicative-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::multiplicativeExpression()
{
  // multiplicative-expression ::= cast-expression (('*' | '/' | '%') cast-expression)*
  return nullptr;
}

std::unique_ptr<Expr> Parser::castExpression()
{
  // cast-expression ::= unary-expression | '(' type-name ')' cast-expression
  return nullptr;
}

std::unique_ptr<Expr> Parser::unaryExpression()
{
  // unary-expression ::= postfix-expression
  //                    | ('++' | '--') unary-expression
  //                    | unary-operator cast-expression
  //                    | 'sizeof' (unary-expression | '(' type-name ')')
  return nullptr;
}

std::unique_ptr<Expr> Parser::postfixExpression()
{
  // postfix-expression ::= primary-expression
  //                      | postfix-expression '[' expression ']'
  //                      | postfix-expression '(' argument-expression-list? ')'
  //                      | postfix-expression '.' identifier
  //                      | postfix-expression '->' identifier
  //                      | postfix-expression ('++' | '--')
  return nullptr;
}

std::unique_ptr<Expr> Parser::primaryExpression()
{
  // primary-expression ::= identifier | constant | string-literal | '(' expression ')'
  return nullptr;
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
