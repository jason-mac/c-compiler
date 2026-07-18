#include <gtest/gtest.h>

#include "token.hpp"

TEST(TokenTest, ConstructsWithGivenValues)
{
  Token token(TokenType::Plus, "+", 1, 5);

  EXPECT_EQ(token.type, TokenType::Plus);
  EXPECT_EQ(token.lexeme, "+");
  EXPECT_EQ(token.line, 1);
  EXPECT_EQ(token.column, 5);
}

TEST(TokenTest, CopyConstructor)
{
  Token token(TokenType::Plus, "+", 1, 5);

  Token token2(token);

  EXPECT_EQ(token.type, TokenType::Plus);
  EXPECT_EQ(token.lexeme, "+");
  EXPECT_EQ(token.line, 1);
  EXPECT_EQ(token.column, 5);

  EXPECT_EQ(token2.type, token.type);
  EXPECT_EQ(token2.lexeme, token.lexeme);
  EXPECT_EQ(token2.line, token.line);
  EXPECT_EQ(token2.column, token.column);
}

TEST(TokenTest, CopyAssignment)
{
  Token token(TokenType::Plus, "+", 1, 5);
  Token token2(TokenType::Int, "int", 2, 10);

  EXPECT_NE(token2.type, token.type);
  EXPECT_NE(token2.lexeme, token.lexeme);
  EXPECT_NE(token2.line, token.line);
  EXPECT_NE(token2.column, token.column);

  token2 = token;

  EXPECT_EQ(token2.type, token.type);
  EXPECT_EQ(token2.lexeme, token.lexeme);
  EXPECT_EQ(token2.line, token.line);
  EXPECT_EQ(token2.column, token.column);
}
