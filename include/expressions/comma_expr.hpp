#pragma once

#include <memory>
#include <vector>

#include "expressions/expr.hpp"

namespace jm
{
struct CommaExpr : Expr
{
  std::vector<std::unique_ptr<Expr>> expressions;

  CommaExpr(std::vector<std::unique_ptr<Expr>> expressions) : expressions(std::move(expressions)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitCommaExpr(*this);
  }
};
} // namespace jm
