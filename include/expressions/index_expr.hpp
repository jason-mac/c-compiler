#pragma once

#include <memory>

#include "expressions/expr.hpp"

namespace jm
{
struct IndexExpr : Expr
{
  std::unique_ptr<Expr> object;
  std::unique_ptr<Expr> index;

  IndexExpr(std::unique_ptr<Expr> object, std::unique_ptr<Expr> index)
      : object(std::move(object)), index(std::move(index))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitIndexExpr(*this);
  }
};
} // namespace jm
