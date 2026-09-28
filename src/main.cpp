#include "lexer.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
std::string_view tokenTypeName(TokenType type)
{
  switch (type)
  {
    case TokenType::EqualEqual: return "EqualEqual";
    case TokenType::NotEqual: return "NotEqual";
    case TokenType::Less: return "Less";
    case TokenType::Greater: return "Greater";
    case TokenType::LessEqual: return "LessEqual";
    case TokenType::GreaterEqual: return "GreaterEqual";
    case TokenType::AndAnd: return "AndAnd";
    case TokenType::OrOr: return "OrOr";
    case TokenType::Not: return "Not";
    case TokenType::Amp: return "Amp";
    case TokenType::Pipe: return "Pipe";
    case TokenType::Caret: return "Caret";
    case TokenType::Tilde: return "Tilde";
    case TokenType::LessLess: return "LessLess";
    case TokenType::GreaterGreater: return "GreaterGreater";
    case TokenType::Equal: return "Equal";
    case TokenType::PlusEqual: return "PlusEqual";
    case TokenType::MinusEqual: return "MinusEqual";
    case TokenType::StarEqual: return "StarEqual";
    case TokenType::SlashEqual: return "SlashEqual";
    case TokenType::PercentEqual: return "PercentEqual";
    case TokenType::AmpEqual: return "AmpEqual";
    case TokenType::PipeEqual: return "PipeEqual";
    case TokenType::CaretEqual: return "CaretEqual";
    case TokenType::LessLessEqual: return "LessLessEqual";
    case TokenType::GreaterGreaterEqual: return "GreaterGreaterEqual";
    case TokenType::Plus: return "Plus";
    case TokenType::Minus: return "Minus";
    case TokenType::Star: return "Star";
    case TokenType::Slash: return "Slash";
    case TokenType::Percent: return "Percent";
    case TokenType::PlusPlus: return "PlusPlus";
    case TokenType::MinusMinus: return "MinusMinus";
    case TokenType::LParen: return "LParen";
    case TokenType::RParen: return "RParen";
    case TokenType::LBrace: return "LBrace";
    case TokenType::RBrace: return "RBrace";
    case TokenType::LBracket: return "LBracket";
    case TokenType::RBracket: return "RBracket";
    case TokenType::Semicolon: return "Semicolon";
    case TokenType::Comma: return "Comma";
    case TokenType::Dot: return "Dot";
    case TokenType::Arrow: return "Arrow";
    case TokenType::Colon: return "Colon";
    case TokenType::Question: return "Question";
    case TokenType::Ellipsis: return "Ellipsis";
    case TokenType::Identifier: return "Identifier";
    case TokenType::IntLiteral: return "IntLiteral";
    case TokenType::FloatLiteral: return "FloatLiteral";
    case TokenType::CharLiteral: return "CharLiteral";
    case TokenType::StringLiteral: return "StringLiteral";
    case TokenType::Auto: return "Auto";
    case TokenType::Break: return "Break";
    case TokenType::Case: return "Case";
    case TokenType::Char: return "Char";
    case TokenType::Const: return "Const";
    case TokenType::Continue: return "Continue";
    case TokenType::Default: return "Default";
    case TokenType::Do: return "Do";
    case TokenType::Double: return "Double";
    case TokenType::Else: return "Else";
    case TokenType::Enum: return "Enum";
    case TokenType::Extern: return "Extern";
    case TokenType::Float: return "Float";
    case TokenType::For: return "For";
    case TokenType::Goto: return "Goto";
    case TokenType::If: return "If";
    case TokenType::Int: return "Int";
    case TokenType::Long: return "Long";
    case TokenType::Register: return "Register";
    case TokenType::Return: return "Return";
    case TokenType::Short: return "Short";
    case TokenType::Signed: return "Signed";
    case TokenType::Sizeof: return "Sizeof";
    case TokenType::Static: return "Static";
    case TokenType::Struct: return "Struct";
    case TokenType::Switch: return "Switch";
    case TokenType::Typedef: return "Typedef";
    case TokenType::Union: return "Union";
    case TokenType::Unsigned: return "Unsigned";
    case TokenType::Void: return "Void";
    case TokenType::Volatile: return "Volatile";
    case TokenType::While: return "While";
    case TokenType::Bool: return "Bool";
    case TokenType::True: return "True";
    case TokenType::False: return "False";
    case TokenType::Nullptr: return "Nullptr";
    case TokenType::Unknown: return "Unknown";
    case TokenType::Eof: return "Eof";
  }
  return "?";
}
} // namespace

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " <source-file>\n";
    return EXIT_FAILURE;
  }

  std::filesystem::path source_path = argv[1];

  std::ifstream file(source_path, std::ios::binary);
  if (!file.is_open())
  {
    std::cerr << "error: could not open file '" << source_path.string() << "'\n";
    return EXIT_FAILURE;
  }

  auto size = std::filesystem::file_size(source_path);
  std::string source(size, '\0');
  file.read(source.data(), static_cast<std::streamsize>(size));

  jm::Lexer lexer(source);
  for (const auto& token : lexer.tokenize())
  {
    std::cout << token.line << ":" << token.column << "  " << tokenTypeName(token.type) << "  "
              << token.lexeme << "\n";
  }

  return 0;
}
