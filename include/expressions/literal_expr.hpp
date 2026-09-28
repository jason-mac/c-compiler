#pragma once

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct LiteralExpr : Expr
{
  Token value;
  LiteralExpr(Token value) : value(std::move(value)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitLiteralExpr(*this);
  }
};
} // namespace jm
