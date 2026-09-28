#pragma once

#include <memory>

#include "expressions/expr.hpp"

namespace jm
{
struct ConditionalExpr : Expr
{
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Expr> thenExpr;
  std::unique_ptr<Expr> elseExpr;

  ConditionalExpr(std::unique_ptr<Expr> condition, std::unique_ptr<Expr> thenExpr,
                  std::unique_ptr<Expr> elseExpr)
      : condition(std::move(condition)), thenExpr(std::move(thenExpr)),
        elseExpr(std::move(elseExpr))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitConditionalExpr(*this);
  }
};
} // namespace jm
