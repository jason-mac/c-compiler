#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"
#include "token.hpp"

namespace jm
{
/*
translation-unit ::= external-declaration+

external-declaration ::= function-definition | declaration

function-definition ::= declaration-specifiers declarator declaration-list? compound-statement

declaration ::= declaration-specifiers init-declarator-list? ';'

declaration-specifiers ::= (storage-class-specifier | type-specifier | type-qualifier)+

storage-class-specifier ::= 'typedef' | 'extern' | 'static' | 'auto' | 'register'

type-specifier ::= 'void' | 'char' | 'short' | 'int' | 'long' | 'float' | 'double'
                  | 'signed' | 'unsigned' | 'bool'
                  | struct-or-union-specifier | enum-specifier | typedef-name

type-qualifier ::= 'const' | 'volatile'

struct-or-union-specifier ::= ('struct' | 'union') identifier? '{' struct-declaration+ '}'
                             | ('struct' | 'union') identifier

struct-declaration ::= (type-specifier | type-qualifier)+ struct-declarator-list ';'

struct-declarator-list ::= struct-declarator (',' struct-declarator)*

struct-declarator ::= declarator | declarator? ':' constant-expression

enum-specifier ::= 'enum' identifier? '{' enumerator-list '}' | 'enum' identifier

enumerator-list ::= enumerator (',' enumerator)*

enumerator ::= identifier ('=' constant-expression)?

init-declarator-list ::= init-declarator (',' init-declarator)*

init-declarator ::= declarator ('=' initializer)?

declarator ::= pointer? direct-declarator

pointer ::= '*' type-qualifier* pointer?

direct-declarator ::= identifier
                     | '(' declarator ')'
                     | direct-declarator '[' constant-expression? ']'
                     | direct-declarator '(' parameter-type-list ')'
                     | direct-declarator '(' identifier-list? ')'

parameter-type-list ::= parameter-list (',' '...')?

parameter-list ::= parameter-declaration (',' parameter-declaration)*

parameter-declaration ::= declaration-specifiers (declarator | abstract-declarator?)

identifier-list ::= identifier (',' identifier)*

initializer ::= assignment-expression | '{' initializer-list ','? '}'

initializer-list ::= initializer (',' initializer)*

declaration-list ::= declaration+

statement ::= labeled-statement
            | compound-statement
            | expression-statement
            | selection-statement
            | iteration-statement
            | jump-statement

labeled-statement ::= identifier ':' statement
                     | 'case' constant-expression ':' statement
                     | 'default' ':' statement

compound-statement ::= '{' (declaration | statement)* '}'

expression-statement ::= expression? ';'

selection-statement ::= 'if' '(' expression ')' statement ('else' statement)?
                       | 'switch' '(' expression ')' statement

iteration-statement ::= 'while' '(' expression ')' statement
                       | 'do' statement 'while' '(' expression ')' ';'
                       | 'for' '(' expression? ';' expression? ';' expression? ')' statement

jump-statement ::= 'goto' identifier ';'
                  | 'continue' ';'
                  | 'break' ';'
                  | 'return' expression? ';'

expression ::= assignment-expression (',' assignment-expression)*

assignment-expression ::= conditional-expression
                         | unary-expression assignment-operator assignment-expression

assignment-operator ::= '=' | '*=' | '/=' | '%=' | '+=' | '-='
                       | '<<=' | '>>=' | '&=' | '^=' | '|='

conditional-expression ::= logical-or-expression ('?' expression ':' conditional-expression)?

constant-expression ::= conditional-expression

logical-or-expression ::= logical-and-expression ('||' logical-and-expression)*

logical-and-expression ::= inclusive-or-expression ('&&' inclusive-or-expression)*

inclusive-or-expression ::= exclusive-or-expression ('|' exclusive-or-expression)*

exclusive-or-expression ::= and-expression ('^' and-expression)*

and-expression ::= equality-expression ('&' equality-expression)*

equality-expression ::= relational-expression (('==' | '!=') relational-expression)*

relational-expression ::= shift-expression (('<' | '>' | '<=' | '>=') shift-expression)*

shift-expression ::= additive-expression (('<<' | '>>') additive-expression)*

additive-expression ::= multiplicative-expression (('+' | '-') multiplicative-expression)*

multiplicative-expression ::= cast-expression (('*' | '/' | '%') cast-expression)*

cast-expression ::= unary-expression | '(' type-name ')' cast-expression

unary-expression ::= postfix-expression
                    | ('++' | '--') unary-expression
                    | unary-operator cast-expression
                    | 'sizeof' (unary-expression | '(' type-name ')')

unary-operator ::= '&' | '*' | '+' | '-' | '~' | '!'

postfix-expression ::= primary-expression
                      | postfix-expression '[' expression ']'
                      | postfix-expression '(' argument-expression-list? ')'
                      | postfix-expression '.' identifier
                      | postfix-expression '->' identifier
                      | postfix-expression ('++' | '--')

argument-expression-list ::= assignment-expression (',' assignment-expression)*

primary-expression ::= identifier | constant | string-literal | '(' expression ')'

constant ::= int-literal | float-literal | char-literal
*/
class ParseError : public std::runtime_error
{
public:
  int line;
  ParseError(const std::string& message, int line) : std::runtime_error(message), line(line) {}
};

class Parser
{
public:
  Parser(std::vector<Token> tokens) : tokens_(std::move(tokens)), pos_(0) {}
  std::vector<std::unique_ptr<Stmt>> parse();

private:
  std::vector<Token> tokens_;
  size_t pos_;

  const Token& advance();
  const Token& peek();
  const Token& peekNext();
  const Token& previous();
  const Token& consume(TokenType type, const std::string& message);
  bool check(TokenType type);
  bool match(std::initializer_list<TokenType> types);
  bool isAtEnd();
  void sync();

  template <typename... TokenTypes> bool match(TokenTypes... types)
  {
    return match({types...});
  }
};
} // namespace jm
