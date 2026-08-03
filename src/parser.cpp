#include <parser.hpp>

namespace jm
{
std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
  return {};
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
