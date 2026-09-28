#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "type.hpp"

namespace jm
{
struct CastExpr : Expr
{
  Type type;
  std::unique_ptr<Expr> expr;

  CastExpr(Type type, std::unique_ptr<Expr> expr) : type(std::move(type)), expr(std::move(expr)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitCastExpr(*this);
  }
};
} // namespace jm
