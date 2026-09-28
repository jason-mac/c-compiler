#pragma once

#include <memory>
#include <optional>

#include "expressions/expr.hpp"
#include "type.hpp"

namespace jm
{
// sizeof expr  -> expr set
// sizeof(type) -> type set
struct SizeofExpr : Expr
{
  std::unique_ptr<Expr> expr;
  std::optional<Type> type;

  SizeofExpr(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}
  SizeofExpr(Type type) : type(std::move(type)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitSizeofExpr(*this);
  }
};
} // namespace jm
