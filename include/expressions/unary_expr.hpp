#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct UnaryExpr : Expr
{
  Token op;
  std::unique_ptr<Expr> right;

  UnaryExpr(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitUnaryExpr(*this);
  }
};
} // namespace jm
