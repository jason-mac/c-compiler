#pragma once

#include <optional>
#include <string_view>
#include <vector>

#include "token.hpp"

namespace jm
{
class Lexer
{
public:
  // TODO: preprocessor directives (#include, #define, etc.) aren't handled
  // TODO: no error reporting yet, bad input silently becomes Unknown or runs to EOF
  Lexer(std::string_view source)
      : source_(source), pos_(0), start_(0), line_(1), column_(1), start_line_(1), start_column_(1)
  {
  }
  std::vector<Token> tokenize();

private:
  std::string_view source_;
  std::vector<Token> tokens_;

  size_t pos_;
  size_t start_;
  int line_;
  int column_;
  int start_line_;
  int start_column_;

  char advance();
  char peek();
  char peekNext();
  bool match(char expected);
  bool isAtEnd();

  std::optional<Token> scanToken();
  Token makeToken(TokenType type);
  Token makeNumberToken();
  Token makeHexNumberToken();
  Token makeBinaryNumberToken();
  Token makeOctalNumberToken();
  std::optional<Token> makeKeywordToken();
  Token makeIdentifierToken();
  Token makeStringToken();
  Token makeCharToken();

  static bool isDigit(char c);
  static bool isAlpha(char c);
  static bool isAlnum(char c);

  template <typename... Chars> static bool isAny(char c, Chars... chars)
  {
    return ((c == chars) || ...);
  }
};
} // namespace jm
