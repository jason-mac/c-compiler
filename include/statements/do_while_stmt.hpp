#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"

namespace jm
{
struct DoWhileStmt : Stmt
{
  std::unique_ptr<Stmt> body;
  std::unique_ptr<Expr> condition;

  DoWhileStmt(std::unique_ptr<Stmt> body, std::unique_ptr<Expr> condition)
      : body(std::move(body)), condition(std::move(condition))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitDoWhileStmt(*this);
  }
};
} // namespace jm
