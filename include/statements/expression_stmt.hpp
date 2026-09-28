#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"

namespace jm
{
struct ExpressionStmt : Stmt
{
  std::unique_ptr<Expr> expr;

  ExpressionStmt(std::unique_ptr<Expr> expr) : expr(std::move(expr)) {}

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitExpressionStmt(*this);
  }
};
} // namespace jm
