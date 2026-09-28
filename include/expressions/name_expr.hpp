#pragma once

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct NameExpr : Expr
{
  Token name;
  NameExpr(Token name) : name(std::move(name)) {}

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitNameExpr(*this);
  }
};
} // namespace jm
