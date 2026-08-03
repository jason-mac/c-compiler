#include <gtest/gtest.h>

#include "lexer.hpp"

TEST(LexerTest, Plus)
{
  jm::Lexer lexer("+");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Plus);
  EXPECT_EQ(tokens[0].lexeme, "+");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, PlusEqual)
{
  jm::Lexer lexer("+=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::PlusEqual);
  EXPECT_EQ(tokens[0].lexeme, "+=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Minus)
{
  jm::Lexer lexer("-");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Minus);
  EXPECT_EQ(tokens[0].lexeme, "-");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MinusEqual)
{
  jm::Lexer lexer("-=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::MinusEqual);
  EXPECT_EQ(tokens[0].lexeme, "-=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Star)
{
  jm::Lexer lexer("*");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Star);
  EXPECT_EQ(tokens[0].lexeme, "*");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, StarEqual)
{
  jm::Lexer lexer("*=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::StarEqual);
  EXPECT_EQ(tokens[0].lexeme, "*=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Slash)
{
  jm::Lexer lexer("/");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Slash);
  EXPECT_EQ(tokens[0].lexeme, "/");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, SlashEqual)
{
  jm::Lexer lexer("/=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::SlashEqual);
  EXPECT_EQ(tokens[0].lexeme, "/=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Percent)
{
  jm::Lexer lexer("%");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Percent);
  EXPECT_EQ(tokens[0].lexeme, "%");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, PercentEqual)
{
  jm::Lexer lexer("%=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::PercentEqual);
  EXPECT_EQ(tokens[0].lexeme, "%=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Colon)
{
  jm::Lexer lexer(":");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Colon);
  EXPECT_EQ(tokens[0].lexeme, ":");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Comma)
{
  jm::Lexer lexer(",");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Comma);
  EXPECT_EQ(tokens[0].lexeme, ",");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Semicolon)
{
  jm::Lexer lexer(";");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Semicolon);
  EXPECT_EQ(tokens[0].lexeme, ";");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LParen)
{
  jm::Lexer lexer("(");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LParen);
  EXPECT_EQ(tokens[0].lexeme, "(");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, RParen)
{
  jm::Lexer lexer(")");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::RParen);
  EXPECT_EQ(tokens[0].lexeme, ")");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LBrace)
{
  jm::Lexer lexer("{");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LBrace);
  EXPECT_EQ(tokens[0].lexeme, "{");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, RBrace)
{
  jm::Lexer lexer("}");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::RBrace);
  EXPECT_EQ(tokens[0].lexeme, "}");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LBracket)
{
  jm::Lexer lexer("[");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LBracket);
  EXPECT_EQ(tokens[0].lexeme, "[");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, RBracket)
{
  jm::Lexer lexer("]");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::RBracket);
  EXPECT_EQ(tokens[0].lexeme, "]");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Question)
{
  jm::Lexer lexer("?");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Question);
  EXPECT_EQ(tokens[0].lexeme, "?");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Tilde)
{
  jm::Lexer lexer("~");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Tilde);
  EXPECT_EQ(tokens[0].lexeme, "~");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Equal)
{
  jm::Lexer lexer("=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Equal);
  EXPECT_EQ(tokens[0].lexeme, "=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, EqualEqual)
{
  jm::Lexer lexer("==");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::EqualEqual);
  EXPECT_EQ(tokens[0].lexeme, "==");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Not)
{
  jm::Lexer lexer("!");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Not);
  EXPECT_EQ(tokens[0].lexeme, "!");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, NotEqual)
{
  jm::Lexer lexer("!=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::NotEqual);
  EXPECT_EQ(tokens[0].lexeme, "!=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Amp)
{
  jm::Lexer lexer("&");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Amp);
  EXPECT_EQ(tokens[0].lexeme, "&");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, AmpEqual)
{
  jm::Lexer lexer("&=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::AmpEqual);
  EXPECT_EQ(tokens[0].lexeme, "&=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, AndAnd)
{
  jm::Lexer lexer("&&");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::AndAnd);
  EXPECT_EQ(tokens[0].lexeme, "&&");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Pipe)
{
  jm::Lexer lexer("|");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Pipe);
  EXPECT_EQ(tokens[0].lexeme, "|");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, PipeEqual)
{
  jm::Lexer lexer("|=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::PipeEqual);
  EXPECT_EQ(tokens[0].lexeme, "|=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, OrOr)
{
  jm::Lexer lexer("||");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::OrOr);
  EXPECT_EQ(tokens[0].lexeme, "||");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Caret)
{
  jm::Lexer lexer("^");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Caret);
  EXPECT_EQ(tokens[0].lexeme, "^");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, CaretEqual)
{
  jm::Lexer lexer("^=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::CaretEqual);
  EXPECT_EQ(tokens[0].lexeme, "^=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, PlusPlus)
{
  jm::Lexer lexer("++");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::PlusPlus);
  EXPECT_EQ(tokens[0].lexeme, "++");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MinusMinus)
{
  jm::Lexer lexer("--");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::MinusMinus);
  EXPECT_EQ(tokens[0].lexeme, "--");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Arrow)
{
  jm::Lexer lexer("->");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Arrow);
  EXPECT_EQ(tokens[0].lexeme, "->");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Less)
{
  jm::Lexer lexer("<");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Less);
  EXPECT_EQ(tokens[0].lexeme, "<");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LessEqual)
{
  jm::Lexer lexer("<=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LessEqual);
  EXPECT_EQ(tokens[0].lexeme, "<=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LessLess)
{
  jm::Lexer lexer("<<");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LessLess);
  EXPECT_EQ(tokens[0].lexeme, "<<");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LessLessEqual)
{
  jm::Lexer lexer("<<=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::LessLessEqual);
  EXPECT_EQ(tokens[0].lexeme, "<<=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Greater)
{
  jm::Lexer lexer(">");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Greater);
  EXPECT_EQ(tokens[0].lexeme, ">");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, GreaterEqual)
{
  jm::Lexer lexer(">=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::GreaterEqual);
  EXPECT_EQ(tokens[0].lexeme, ">=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, GreaterGreater)
{
  jm::Lexer lexer(">>");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::GreaterGreater);
  EXPECT_EQ(tokens[0].lexeme, ">>");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, GreaterGreaterEqual)
{
  jm::Lexer lexer(">>=");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::GreaterGreaterEqual);
  EXPECT_EQ(tokens[0].lexeme, ">>=");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Dot)
{
  jm::Lexer lexer(".");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Dot);
  EXPECT_EQ(tokens[0].lexeme, ".");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, DotDotIsTwoDotTokens)
{
  jm::Lexer lexer("..");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0].type, TokenType::Dot);
  EXPECT_EQ(tokens[0].lexeme, ".");
  EXPECT_EQ(tokens[1].type, TokenType::Dot);
  EXPECT_EQ(tokens[1].lexeme, ".");
  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, Ellipsis)
{
  jm::Lexer lexer("...");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Ellipsis);
  EXPECT_EQ(tokens[0].lexeme, "...");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Unknown)
{
  jm::Lexer lexer("@");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Unknown);
  EXPECT_EQ(tokens[0].lexeme, "@");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteral)
{
  jm::Lexer lexer("42");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, FloatLiteral)
{
  jm::Lexer lexer("3.14");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::FloatLiteral);
  EXPECT_EQ(tokens[0].lexeme, "3.14");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordAuto)
{
  jm::Lexer lexer("auto");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Auto);
  EXPECT_EQ(tokens[0].lexeme, "auto");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordBreak)
{
  jm::Lexer lexer("break");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Break);
  EXPECT_EQ(tokens[0].lexeme, "break");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordCase)
{
  jm::Lexer lexer("case");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Case);
  EXPECT_EQ(tokens[0].lexeme, "case");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordChar)
{
  jm::Lexer lexer("char");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Char);
  EXPECT_EQ(tokens[0].lexeme, "char");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordConst)
{
  jm::Lexer lexer("const");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Const);
  EXPECT_EQ(tokens[0].lexeme, "const");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordContinue)
{
  jm::Lexer lexer("continue");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Continue);
  EXPECT_EQ(tokens[0].lexeme, "continue");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordDefault)
{
  jm::Lexer lexer("default");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Default);
  EXPECT_EQ(tokens[0].lexeme, "default");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordDo)
{
  jm::Lexer lexer("do");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Do);
  EXPECT_EQ(tokens[0].lexeme, "do");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordDouble)
{
  jm::Lexer lexer("double");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Double);
  EXPECT_EQ(tokens[0].lexeme, "double");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordElse)
{
  jm::Lexer lexer("else");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Else);
  EXPECT_EQ(tokens[0].lexeme, "else");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordEnum)
{
  jm::Lexer lexer("enum");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Enum);
  EXPECT_EQ(tokens[0].lexeme, "enum");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordExtern)
{
  jm::Lexer lexer("extern");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Extern);
  EXPECT_EQ(tokens[0].lexeme, "extern");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordFloat)
{
  jm::Lexer lexer("float");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Float);
  EXPECT_EQ(tokens[0].lexeme, "float");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordFor)
{
  jm::Lexer lexer("for");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::For);
  EXPECT_EQ(tokens[0].lexeme, "for");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordGoto)
{
  jm::Lexer lexer("goto");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Goto);
  EXPECT_EQ(tokens[0].lexeme, "goto");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordIf)
{
  jm::Lexer lexer("if");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::If);
  EXPECT_EQ(tokens[0].lexeme, "if");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordInt)
{
  jm::Lexer lexer("int");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Int);
  EXPECT_EQ(tokens[0].lexeme, "int");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordLong)
{
  jm::Lexer lexer("long");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Long);
  EXPECT_EQ(tokens[0].lexeme, "long");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordRegister)
{
  jm::Lexer lexer("register");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Register);
  EXPECT_EQ(tokens[0].lexeme, "register");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordReturn)
{
  jm::Lexer lexer("return");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Return);
  EXPECT_EQ(tokens[0].lexeme, "return");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordShort)
{
  jm::Lexer lexer("short");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Short);
  EXPECT_EQ(tokens[0].lexeme, "short");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordSigned)
{
  jm::Lexer lexer("signed");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Signed);
  EXPECT_EQ(tokens[0].lexeme, "signed");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordSizeof)
{
  jm::Lexer lexer("sizeof");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Sizeof);
  EXPECT_EQ(tokens[0].lexeme, "sizeof");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordStatic)
{
  jm::Lexer lexer("static");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Static);
  EXPECT_EQ(tokens[0].lexeme, "static");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordStruct)
{
  jm::Lexer lexer("struct");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Struct);
  EXPECT_EQ(tokens[0].lexeme, "struct");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordSwitch)
{
  jm::Lexer lexer("switch");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Switch);
  EXPECT_EQ(tokens[0].lexeme, "switch");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordTypedef)
{
  jm::Lexer lexer("typedef");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Typedef);
  EXPECT_EQ(tokens[0].lexeme, "typedef");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordUnion)
{
  jm::Lexer lexer("union");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Union);
  EXPECT_EQ(tokens[0].lexeme, "union");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordUnsigned)
{
  jm::Lexer lexer("unsigned");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Unsigned);
  EXPECT_EQ(tokens[0].lexeme, "unsigned");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordVoid)
{
  jm::Lexer lexer("void");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Void);
  EXPECT_EQ(tokens[0].lexeme, "void");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordVolatile)
{
  jm::Lexer lexer("volatile");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Volatile);
  EXPECT_EQ(tokens[0].lexeme, "volatile");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordWhile)
{
  jm::Lexer lexer("while");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::While);
  EXPECT_EQ(tokens[0].lexeme, "while");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordBool)
{
  jm::Lexer lexer("bool");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Bool);
  EXPECT_EQ(tokens[0].lexeme, "bool");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordTrue)
{
  jm::Lexer lexer("true");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::True);
  EXPECT_EQ(tokens[0].lexeme, "true");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordFalse)
{
  jm::Lexer lexer("false");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::False);
  EXPECT_EQ(tokens[0].lexeme, "false");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, KeywordNullptr)
{
  jm::Lexer lexer("nullptr");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Nullptr);
  EXPECT_EQ(tokens[0].lexeme, "nullptr");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, Identifier)
{
  jm::Lexer lexer("foo");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "foo");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IdentifierWithUnderscore)
{
  jm::Lexer lexer("_foo_bar_1");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "_foo_bar_1");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MultipleTokensOnOneLineTrackColumns)
{
  jm::Lexer lexer("int x = 42;");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 6);

  EXPECT_EQ(tokens[0].type, TokenType::Int);
  EXPECT_EQ(tokens[0].lexeme, "int");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "x");
  EXPECT_EQ(tokens[1].line, 1);
  EXPECT_EQ(tokens[1].column, 5);

  EXPECT_EQ(tokens[2].type, TokenType::Equal);
  EXPECT_EQ(tokens[2].lexeme, "=");
  EXPECT_EQ(tokens[2].line, 1);
  EXPECT_EQ(tokens[2].column, 7);

  EXPECT_EQ(tokens[3].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[3].lexeme, "42");
  EXPECT_EQ(tokens[3].line, 1);
  EXPECT_EQ(tokens[3].column, 9);

  EXPECT_EQ(tokens[4].type, TokenType::Semicolon);
  EXPECT_EQ(tokens[4].lexeme, ";");
  EXPECT_EQ(tokens[4].line, 1);
  EXPECT_EQ(tokens[4].column, 11);

  EXPECT_EQ(tokens[5].type, TokenType::Eof);
}

TEST(LexerTest, TokensAcrossMultipleLinesTrackLineAndColumn)
{
  jm::Lexer lexer("int\nx");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Int);
  EXPECT_EQ(tokens[0].lexeme, "int");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "x");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, TabAdvancesColumnLikeASingleCharacter)
{
  jm::Lexer lexer("\tx");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 2);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MultipleLinesWithBlankLineTracksLineNumber)
{
  jm::Lexer lexer("a\n\nb");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 3);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, StringLiteral)
{
  jm::Lexer lexer("\"hello world\"");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::StringLiteral);
  EXPECT_EQ(tokens[0].lexeme, "\"hello world\"");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, StringLiteralWithEscapedQuote)
{
  jm::Lexer lexer(R"("say \"hi\"")");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::StringLiteral);
  EXPECT_EQ(tokens[0].lexeme, R"("say \"hi\"")");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, UnterminatedStringLiteral)
{
  jm::Lexer lexer("\"unterminated");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::StringLiteral);
  EXPECT_EQ(tokens[0].lexeme, "\"unterminated");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, CharLiteral)
{
  jm::Lexer lexer("'a'");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::CharLiteral);
  EXPECT_EQ(tokens[0].lexeme, "'a'");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IdentifierWithKeywordPrefixIsNotSplit)
{
  jm::Lexer lexer("int1");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "int1");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IdentifierWithKeywordPrefixAndUnderscoreIsNotSplit)
{
  jm::Lexer lexer("while_loop");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "while_loop");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentIsSkipped)
{
  jm::Lexer lexer("/* comment */");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentWithStrayStarIsFullyConsumed)
{
  jm::Lexer lexer("/* a * b */ x");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, UnterminatedBlockCommentConsumesToEnd)
{
  jm::Lexer lexer("/* unterminated");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentBetweenTokensTracksColumns)
{
  jm::Lexer lexer("a /* comment */ b");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 1);
  EXPECT_EQ(tokens[1].column, 17);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentAdjacentToTokensNoWhitespace)
{
  jm::Lexer lexer("a/*c*/b");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 1);
  EXPECT_EQ(tokens[1].column, 7);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentSpanningMultipleLinesUpdatesLineAndColumn)
{
  jm::Lexer lexer("a /* line1\nline2 */ b");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 10);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, BlockCommentWithLoneSlashIsFullyConsumed)
{
  jm::Lexer lexer("/* / not end */ x");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 17);

  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MultipleBlockCommentsBetweenTokens)
{
  jm::Lexer lexer("/* one */ x /* two */ y");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 11);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "y");
  EXPECT_EQ(tokens[1].line, 1);
  EXPECT_EQ(tokens[1].column, 23);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentAtEndOfFileIsSkipped)
{
  jm::Lexer lexer("// comment");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentEndsAtNewline)
{
  jm::Lexer lexer("// comment\nx");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 2);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentBetweenTokensTracksLineAndColumn)
{
  jm::Lexer lexer("a // comment\nb");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentAdjacentToTokenNoWhitespace)
{
  jm::Lexer lexer("a//c\nb");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentContainingStarsAndSlashesIsFullyConsumed)
{
  jm::Lexer lexer("// still * / a comment\nx");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 2);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, MultipleLineCommentsBetweenTokens)
{
  jm::Lexer lexer("// one\nx // two\ny");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 2);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "y");
  EXPECT_EQ(tokens[1].line, 3);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, LineCommentDoesNotConsumeSubsequentLine)
{
  jm::Lexer lexer("// comment\n// another\nx");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "x");
  EXPECT_EQ(tokens[0].line, 3);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, BackslashNewlineContinuationIsSkipped)
{
  jm::Lexer lexer("a\\\nb");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 1);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, BackslashNewlineContinuationWithSurroundingWhitespace)
{
  jm::Lexer lexer("a \\\n b");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Identifier);
  EXPECT_EQ(tokens[1].lexeme, "b");
  EXPECT_EQ(tokens[1].line, 2);
  EXPECT_EQ(tokens[1].column, 2);

  EXPECT_EQ(tokens[2].type, TokenType::Eof);
}

TEST(LexerTest, BareBackslashNotFollowedByNewlineIsUnknown)
{
  jm::Lexer lexer("a\\b");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 4);

  EXPECT_EQ(tokens[0].type, TokenType::Identifier);
  EXPECT_EQ(tokens[0].lexeme, "a");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);

  EXPECT_EQ(tokens[1].type, TokenType::Unknown);
  EXPECT_EQ(tokens[1].lexeme, "\\");
  EXPECT_EQ(tokens[1].line, 1);
  EXPECT_EQ(tokens[1].column, 2);

  EXPECT_EQ(tokens[2].type, TokenType::Identifier);
  EXPECT_EQ(tokens[2].lexeme, "b");
  EXPECT_EQ(tokens[2].line, 1);
  EXPECT_EQ(tokens[2].column, 3);

  EXPECT_EQ(tokens[3].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUSuffix)
{
  jm::Lexer lexer("42u");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42u");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithLSuffix)
{
  jm::Lexer lexer("42l");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42l");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithLLSuffix)
{
  jm::Lexer lexer("42ll");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42ll");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithULLSuffix)
{
  jm::Lexer lexer("42ull");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42ull");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperUSuffix)
{
  jm::Lexer lexer("42U");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42U");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperLSuffix)
{
  jm::Lexer lexer("42L");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42L");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperLLSuffix)
{
  jm::Lexer lexer("42LL");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42LL");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithULSuffix)
{
  jm::Lexer lexer("42ul");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42ul");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperULSuffix)
{
  jm::Lexer lexer("42UL");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42UL");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithMixedCaseULSuffix)
{
  jm::Lexer lexer("42uL");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42uL");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithLUSuffix)
{
  jm::Lexer lexer("42lu");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42lu");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperLUSuffix)
{
  jm::Lexer lexer("42LU");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42LU");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithMixedCaseLUSuffix)
{
  jm::Lexer lexer("42lU");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42lU");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperULLSuffix)
{
  jm::Lexer lexer("42ULL");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42ULL");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithMixedCaseULLSuffix)
{
  jm::Lexer lexer("42uLL");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42uLL");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithLLUSuffix)
{
  jm::Lexer lexer("42llu");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42llu");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithUpperLLUSuffix)
{
  jm::Lexer lexer("42LLU");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42LLU");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, IntLiteralWithMixedCaseLLUSuffix)
{
  jm::Lexer lexer("42llU");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "42llU");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, HexIntLiteral)
{
  jm::Lexer lexer("0x1F");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "0x1F");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, HexIntLiteralUppercasePrefix)
{
  jm::Lexer lexer("0X1f");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "0X1f");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, BinaryIntLiteral)
{
  jm::Lexer lexer("0b1010");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "0b1010");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, BinaryIntLiteralUppercasePrefix)
{
  jm::Lexer lexer("0B1010");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "0B1010");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, OctalIntLiteral)
{
  jm::Lexer lexer("012");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "012");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

TEST(LexerTest, ZeroAloneIsIntLiteral)
{
  jm::Lexer lexer("0");
  auto tokens = lexer.tokenize();

  ASSERT_EQ(tokens.size(), 2);
  EXPECT_EQ(tokens[0].type, TokenType::IntLiteral);
  EXPECT_EQ(tokens[0].lexeme, "0");
  EXPECT_EQ(tokens[0].line, 1);
  EXPECT_EQ(tokens[0].column, 1);
  EXPECT_EQ(tokens[1].type, TokenType::Eof);
}

namespace
{
void ExpectTypes(const std::vector<Token>& tokens, const std::vector<TokenType>& expected)
{
  ASSERT_EQ(tokens.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i)
  {
    EXPECT_EQ(tokens[i].type, expected[i]) << "at index " << i;
  }
}
} // namespace

TEST(LexerTest, FunctionDefinition)
{
  jm::Lexer lexer(R"(int add(int a, int b) {
    return a + b;
})");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::LParen,
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::Comma,
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::RParen,
                          TokenType::LBrace,
                          TokenType::Return,
                          TokenType::Identifier,
                          TokenType::Plus,
                          TokenType::Identifier,
                          TokenType::Semicolon,
                          TokenType::RBrace,
                          TokenType::Eof,
                      });

  EXPECT_EQ(tokens[1].lexeme, "add");
  EXPECT_EQ(tokens[4].lexeme, "a");
  EXPECT_EQ(tokens[7].lexeme, "b");
}

TEST(LexerTest, ForLoop)
{
  jm::Lexer lexer(R"(for (int i = 0; i < 10; i++) {
    sum += i;
})");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::For,        TokenType::LParen,     TokenType::Int,
                          TokenType::Identifier, TokenType::Equal,      TokenType::IntLiteral,
                          TokenType::Semicolon,  TokenType::Identifier, TokenType::Less,
                          TokenType::IntLiteral, TokenType::Semicolon,  TokenType::Identifier,
                          TokenType::PlusPlus,   TokenType::RParen,     TokenType::LBrace,
                          TokenType::Identifier, TokenType::PlusEqual,  TokenType::Identifier,
                          TokenType::Semicolon,  TokenType::RBrace,     TokenType::Eof,
                      });

  EXPECT_EQ(tokens[3].lexeme, "i");
  EXPECT_EQ(tokens[5].lexeme, "0");
  EXPECT_EQ(tokens[9].lexeme, "10");
}

TEST(LexerTest, StructDeclaration)
{
  jm::Lexer lexer(R"(struct Point {
    int x;
    int y;
};)");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::Struct,
                          TokenType::Identifier,
                          TokenType::LBrace,
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::Semicolon,
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::Semicolon,
                          TokenType::RBrace,
                          TokenType::Semicolon,
                          TokenType::Eof,
                      });

  EXPECT_EQ(tokens[1].lexeme, "Point");
  EXPECT_EQ(tokens[4].lexeme, "x");
  EXPECT_EQ(tokens[7].lexeme, "y");
}

TEST(LexerTest, IfElseWithComparisonAndLogicalOperators)
{
  jm::Lexer lexer(R"(if (x > 0 && y != 0) {
    return x / y;
} else {
    return 0;
})");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::If,         TokenType::LParen,     TokenType::Identifier,
                          TokenType::Greater,    TokenType::IntLiteral, TokenType::AndAnd,
                          TokenType::Identifier, TokenType::NotEqual,   TokenType::IntLiteral,
                          TokenType::RParen,     TokenType::LBrace,     TokenType::Return,
                          TokenType::Identifier, TokenType::Slash,      TokenType::Identifier,
                          TokenType::Semicolon,  TokenType::RBrace,     TokenType::Else,
                          TokenType::LBrace,     TokenType::Return,     TokenType::IntLiteral,
                          TokenType::Semicolon,  TokenType::RBrace,     TokenType::Eof,
                      });
}

TEST(LexerTest, CommentsAreSkippedInRealCode)
{
  jm::Lexer lexer("// compute area\nfloat area = 3.14f * r * r; /* pi * r^2 */");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::Float,
                          TokenType::Identifier,
                          TokenType::Equal,
                          TokenType::FloatLiteral,
                          TokenType::Star,
                          TokenType::Identifier,
                          TokenType::Star,
                          TokenType::Identifier,
                          TokenType::Semicolon,
                          TokenType::Eof,
                      });

  EXPECT_EQ(tokens[0].line, 2);
  EXPECT_EQ(tokens[3].lexeme, "3.14f");
}

TEST(LexerTest, PointerDeclarationWithString)
{
  jm::Lexer lexer(R"(char *msg = "hello, world!";)");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::Char,
                          TokenType::Star,
                          TokenType::Identifier,
                          TokenType::Equal,
                          TokenType::StringLiteral,
                          TokenType::Semicolon,
                          TokenType::Eof,
                      });

  EXPECT_EQ(tokens[4].lexeme, R"("hello, world!")");
}

TEST(LexerTest, BitwiseAndShiftCombination)
{
  jm::Lexer lexer("unsigned int flags = (a << 2) | (b & 0xFF);");
  auto tokens = lexer.tokenize();

  ExpectTypes(tokens, {
                          TokenType::Unsigned,
                          TokenType::Int,
                          TokenType::Identifier,
                          TokenType::Equal,
                          TokenType::LParen,
                          TokenType::Identifier,
                          TokenType::LessLess,
                          TokenType::IntLiteral,
                          TokenType::RParen,
                          TokenType::Pipe,
                          TokenType::LParen,
                          TokenType::Identifier,
                          TokenType::Amp,
                          TokenType::IntLiteral,
                          TokenType::RParen,
                          TokenType::Semicolon,
                          TokenType::Eof,
                      });

  EXPECT_EQ(tokens[13].lexeme, "0xFF");
}
