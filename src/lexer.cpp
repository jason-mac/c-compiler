#include <lexer.hpp>

namespace jm
{
std::vector<Token> Lexer::tokenize()
{
  return {};
}

void Lexer::advance() {}

char Lexer::peek()
{
  return '\0';
}

char Lexer::peekNext()
{
  return '\0';
}

bool Lexer::match(char expected)
{
  return false;
}

bool Lexer::isAtEnd()
{
  return false;
}

Token Lexer::makeToken(TokenType type)
{
  return Token(type, "", 0, 0);
}

bool Lexer::isDigit(char c)
{
  return false;
}

bool Lexer::isAlpha(char c)
{
  return false;
}

bool Lexer::isAlnum(char c)
{
  return false;
}

} // namespace jm
