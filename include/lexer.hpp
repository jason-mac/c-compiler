#pragma once

#include <string_view>
#include <vector>

#include "token.hpp"

namespace jm
{
class Lexer
{
public:
  Lexer(std::string_view source) : source_(source), pos_(0), start_(0), line_(1), column_(1) {}
  std::vector<Token> tokenize();

private:
  std::string_view source_;
  std::vector<Token> tokens_;

  size_t pos_;
  size_t start_;
  int line_;
  int column_;

  void advance();
  char peek();
  char peekNext();
  bool match(char expected);
  bool isAtEnd();

  Token makeToken(TokenType type);

  static bool isDigit(char c);
  static bool isAlpha(char c);
  static bool isAlnum(char c);
};
} // namespace jm
