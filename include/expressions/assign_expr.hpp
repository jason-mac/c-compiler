#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct AssignExpr : Expr
{
  std::unique_ptr<Expr> target;
  Token op; // = += -= *= /= %= &= |= ^= <<= >>=
  std::unique_ptr<Expr> value;

  AssignExpr(std::unique_ptr<Expr> target, Token op, std::unique_ptr<Expr> value)
      : target(std::move(target)), op(std::move(op)), value(std::move(value))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitAssignExpr(*this);
  }
};
} // namespace jm
