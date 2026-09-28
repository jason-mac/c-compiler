#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct BinaryExpr : Expr
{
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
      : left(std::move(left)), op(std::move(op)), right(std::move(right))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitBinaryExpr(*this);
  }
};
} // namespace jm
