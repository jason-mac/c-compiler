#include "token.hpp"
#include <lexer.hpp>
#include <unordered_map>
#include <utility>

namespace jm
{
namespace
{
const std::unordered_map<std::string_view, TokenType> kKeywords = {
    {"auto", TokenType::Auto},         {"break", TokenType::Break},
    {"case", TokenType::Case},         {"char", TokenType::Char},
    {"const", TokenType::Const},       {"continue", TokenType::Continue},
    {"default", TokenType::Default},   {"do", TokenType::Do},
    {"double", TokenType::Double},     {"else", TokenType::Else},
    {"enum", TokenType::Enum},         {"extern", TokenType::Extern},
    {"float", TokenType::Float},       {"for", TokenType::For},
    {"goto", TokenType::Goto},         {"if", TokenType::If},
    {"int", TokenType::Int},           {"long", TokenType::Long},
    {"register", TokenType::Register}, {"return", TokenType::Return},
    {"short", TokenType::Short},       {"signed", TokenType::Signed},
    {"sizeof", TokenType::Sizeof},     {"static", TokenType::Static},
    {"struct", TokenType::Struct},     {"switch", TokenType::Switch},
    {"typedef", TokenType::Typedef},   {"union", TokenType::Union},
    {"unsigned", TokenType::Unsigned}, {"void", TokenType::Void},
    {"volatile", TokenType::Volatile}, {"while", TokenType::While},
    {"bool", TokenType::Bool},         {"true", TokenType::True},
    {"false", TokenType::False},       {"nullptr", TokenType::Nullptr},
};

std::optional<TokenType> keywordType(std::string_view lexeme)
{
  auto it = kKeywords.find(lexeme);
  if (it == kKeywords.end()) return std::nullopt;
  return it->second;
}
} // namespace

std::vector<Token> Lexer::tokenize()
{
  while (!isAtEnd())
  {
    for (;;)
    {
      if (isAny(peek(), ' ', '\t', '\r', '\n'))
      {
        advance();
      }
      else if (peek() == '\\' && peekNext() == '\n')
      {
        advance();
        advance();
      }
      else
      {
        break;
      }
    }
    if (isAtEnd()) break;
    start_ = pos_;
    start_line_ = line_;
    start_column_ = column_;
    if (auto tok = scanToken()) tokens_.push_back(*tok);
  }
  tokens_.push_back(Token(TokenType::Eof, "", line_, column_));
  return tokens_;
}

char Lexer::advance()
{
  char c = source_[pos_];
  pos_++;
  if (c == '\n')
  {
    line_++;
    column_ = 1;
  }
  else
  {
    column_++;
  }
  return c;
}

char Lexer::peek()
{
  return isAtEnd() ? '\0' : source_[pos_];
}

char Lexer::peekNext()
{
  return pos_ + 1 >= source_.size() ? '\0' : source_[pos_ + 1];
}

bool Lexer::match(char expected)
{
  if (isAtEnd() || expected != source_[pos_])
  {
    return false;
  }
  advance();
  return true;
}

bool Lexer::isAtEnd()
{
  return pos_ >= source_.size();
}

std::optional<Token> Lexer::scanToken()
{
  auto c = advance();
  switch (c)
  {
    case '+':
    {
      if (match('=')) return makeToken(TokenType::PlusEqual);
      if (match('+')) return makeToken(TokenType::PlusPlus);
      return makeToken(TokenType::Plus);
    }
    case '-':
    {
      if (match('=')) return makeToken(TokenType::MinusEqual);
      if (match('-')) return makeToken(TokenType::MinusMinus);
      if (match('>')) return makeToken(TokenType::Arrow);
      return makeToken(TokenType::Minus);
    }
    case '*': return makeToken(match('=') ? TokenType::StarEqual : TokenType::Star);
    case '/':
    {
      if (match('*'))
      {
        while (!isAtEnd() && !(peek() == '*' && peekNext() == '/')) advance();
        if (!isAtEnd())
        {
          advance();
          advance();
        }
        return std::nullopt;
      }
      if (match('/'))
      {
        while (!isAtEnd() && peek() != '\n') advance();
        if (!isAtEnd())
        {
          advance();
        }
        return std::nullopt;
      }
      return makeToken(match('=') ? TokenType::SlashEqual : TokenType::Slash);
    }
    case '%': return makeToken(match('=') ? TokenType::PercentEqual : TokenType::Percent);
    case '=': return makeToken(match('=') ? TokenType::EqualEqual : TokenType::Equal);
    case '!': return makeToken(match('=') ? TokenType::NotEqual : TokenType::Not);
    case '&':
    {
      if (match('=')) return makeToken(TokenType::AmpEqual);
      if (match('&')) return makeToken(TokenType::AndAnd);
      return makeToken(TokenType::Amp);
    }
    case '|':
    {
      if (match('=')) return makeToken(TokenType::PipeEqual);
      if (match('|')) return makeToken(TokenType::OrOr);
      return makeToken(TokenType::Pipe);
    }
    case '^': return makeToken(match('=') ? TokenType::CaretEqual : TokenType::Caret);
    case '<':
    {
      if (match('=')) return makeToken(TokenType::LessEqual);
      if (match('<'))
      {
        if (match('=')) return makeToken(TokenType::LessLessEqual);
        return makeToken(TokenType::LessLess);
      }
      return makeToken(TokenType::Less);
    }
    case '>':
    {
      if (match('=')) return makeToken(TokenType::GreaterEqual);
      if (match('>'))
      {
        if (match('=')) return makeToken(TokenType::GreaterGreaterEqual);
        return makeToken(TokenType::GreaterGreater);
      }
      return makeToken(TokenType::Greater);
    }
    case '.':
    {
      if (peek() == '.' && peekNext() == '.')
      {
        advance();
        advance();
        return makeToken(TokenType::Ellipsis);
      }
      return makeToken(TokenType::Dot);
    }
    case ':': return makeToken(TokenType::Colon);
    case ',': return makeToken(TokenType::Comma);
    case ';': return makeToken(TokenType::Semicolon);
    case '(': return makeToken(TokenType::LParen);
    case ')': return makeToken(TokenType::RParen);
    case '{': return makeToken(TokenType::LBrace);
    case '}': return makeToken(TokenType::RBrace);
    case '[': return makeToken(TokenType::LBracket);
    case ']': return makeToken(TokenType::RBracket);
    case '?': return makeToken(TokenType::Question);
    case '~': return makeToken(TokenType::Tilde);
    case '"': return makeStringToken();
    case '\'': return makeCharToken();
    default:
    {
      if (isDigit(c))
      {
        if (c == '0')
        {
          if (isAny(peek(), 'x', 'X')) return makeHexNumberToken();
          if (isAny(peek(), 'b', 'B')) return makeBinaryNumberToken();
          if (isAny(peek(), '0', '1', '2', '3', '4', '5', '6', '7')) return makeOctalNumberToken();
        }
        return makeNumberToken();
      }
      else if (isAlpha(c))
      {
        while (isAlnum(peek())) advance();
        if (auto token = makeKeywordToken()) return token.value();
        return makeIdentifierToken();
      }
      return makeToken(TokenType::Unknown);
    }
  }
  std::unreachable();
}

Token Lexer::makeToken(TokenType type)
{
  return Token(type, source_.substr(start_, pos_ - start_), start_line_, start_column_);
}

Token Lexer::makeNumberToken()
{
  while (isDigit(peek())) advance();
  if (match('L'))
  {
    if (match('U')) return makeToken(TokenType::IntLiteral);
    if (match('L'))
    {
      if (match('U')) return makeToken(TokenType::IntLiteral);
      return makeToken(TokenType::IntLiteral);
    }
    return makeToken(TokenType::IntLiteral);
  }
  if (match('l'))
  {
    if (match('u') || match('U')) return makeToken(TokenType::IntLiteral);
    if (match('l'))
    {
      if (match('U') || match('u')) return makeToken(TokenType::IntLiteral);
      return makeToken(TokenType::IntLiteral);
    }
    return makeToken(TokenType::IntLiteral);
  }
  if (match('u') || match('U'))
  {
    if (!isAtEnd() &&
        ((peek() == 'l' && peekNext() == 'l') || (peek() == 'L' && peekNext() == 'L')))
    {
      advance();
      advance();
      return makeToken(TokenType::IntLiteral);
    }
    if (match('l') || match('L')) return makeToken(TokenType::IntLiteral);
    return makeToken(TokenType::IntLiteral);
  }
  if (!match('.')) return makeToken(TokenType::IntLiteral);
  while (isDigit(peek())) advance();
  if (isAny(peek(), 'f', 'F', 'l', 'L')) advance();
  return makeToken(TokenType::FloatLiteral);
}

Token Lexer::makeHexNumberToken()
{
  advance();
  while (isDigit(peek()) ||
         isAny(peek(), 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'))
  {
    advance();
  }
  return makeToken(TokenType::IntLiteral);
}

Token Lexer::makeBinaryNumberToken()
{
  advance();
  while (isAny(peek(), '0', '1')) advance();
  return makeToken(TokenType::IntLiteral);
}

Token Lexer::makeOctalNumberToken()
{
  while (isAny(peek(), '0', '1', '2', '3', '4', '5', '6', '7')) advance();
  return makeToken(TokenType::IntLiteral);
}

std::optional<Token> Lexer::makeKeywordToken()
{
  auto keyword = source_.substr(start_, pos_ - start_);
  if (auto type = keywordType(keyword)) return makeToken(*type);
  return std::nullopt;
}

Token Lexer::makeIdentifierToken()
{
  return makeToken(TokenType::Identifier);
}

Token Lexer::makeStringToken()
{
  while (!isAtEnd() && peek() != '"')
  {
    if (peek() == '\\') advance();
    if (!isAtEnd()) advance();
  }
  if (!isAtEnd()) advance();
  return makeToken(TokenType::StringLiteral);
}

Token Lexer::makeCharToken()
{
  while (!isAtEnd() && peek() != '\'')
  {
    if (peek() == '\\') advance();
    if (!isAtEnd()) advance();
  }
  if (!isAtEnd()) advance();
  return makeToken(TokenType::CharLiteral);
}

bool Lexer::isDigit(char c)
{
  return '0' <= c && c <= '9';
}

bool Lexer::isAlpha(char c)
{
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool Lexer::isAlnum(char c)
{
  return isDigit(c) || isAlpha(c);
}

} // namespace jm
