#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct FieldExpr : Expr
{
  std::unique_ptr<Expr> object;
  Token op; // Dot or Arrow
  Token field;

  FieldExpr(std::unique_ptr<Expr> object, Token op, Token field)
      : object(std::move(object)), op(std::move(op)), field(std::move(field))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitFieldExpr(*this);
  }
};
} // namespace jm
