#pragma once
#include <string_view>

enum class TokenType
{
  // Relational
  EqualEqual,   // ==
  NotEqual,     // !=
  Less,         // <
  Greater,      // >
  LessEqual,    // <=
  GreaterEqual, // >=

  // Logical
  AndAnd, // &&
  OrOr,   // ||
  Not,    // !

  // Bitwise
  Amp,            // &
  Pipe,           // |
  Caret,          // ^
  Tilde,          // ~
  LessLess,       // <<
  GreaterGreater, // >>

  // Assignment
  Equal,               // =
  PlusEqual,           // +=
  MinusEqual,          // -=
  StarEqual,           // *=
  SlashEqual,          // /=
  PercentEqual,        // %=
  AmpEqual,            // &=
  PipeEqual,           // |=
  CaretEqual,          // ^=
  LessLessEqual,       // <<=
  GreaterGreaterEqual, // >>=

  // Arithmetic
  Plus,    // +
  Minus,   // -
  Star,    // *
  Slash,   // /
  Percent, // %

  // Increment/Decrement
  PlusPlus,   // ++
  MinusMinus, // --

  // Punctuation
  LParen,    // (
  RParen,    // )
  LBrace,    // {
  RBrace,    // }
  LBracket,  // [
  RBracket,  // ]
  Semicolon, // ;
  Comma,     // ,
  Dot,       // .
  Arrow,     // ->
  Colon,     // :
  Question,  // ?
  Ellipsis,  // ...

  Identifier, // e.g. foo, x

  // Literals
  IntLiteral,    // e.g. 42
  FloatLiteral,  // e.g. 3.14
  CharLiteral,   // e.g. 'a'
  StringLiteral, // e.g. "hello world"

  // Key words
  Auto,     // auto
  Break,    // break
  Case,     // case
  Char,     // char
  Const,    // const
  Continue, // continue
  Default,  // default
  Do,       // do
  Double,   // double
  Else,     // else
  Enum,     // enum
  Extern,   // extern
  Float,    // float
  For,      // for
  Goto,     // goto
  If,       // if
  Int,      // int
  Long,     // long
  Register, // register
  Return,   // return
  Short,    // short
  Signed,   // signed
  Sizeof,   // sizeof
  Static,   // static
  Struct,   // struct
  Switch,   // switch
  Typedef,  // typedef
  Union,    // union
  Unsigned, // unsigned
  Void,     // void
  Volatile, // volatile
  While,    // while
  Bool,     // bool
  True,     // true
  False,    // false
  Nullptr,  // nullptr

  Unknown, // unrecognized character

  Eof, // End of File
};

class Token
{
public:
  TokenType type;
  std::string_view lexeme;
  int line;
  int column;

public:
  Token(TokenType type, std::string_view lexeme, int line, int column)
      : type(type), lexeme(lexeme), line(line), column(column)
  {
  }
};
