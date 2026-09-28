#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"

namespace jm
{
struct WhileStmt : Stmt
{
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> body;

  WhileStmt(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> body)
      : condition(std::move(condition)), body(std::move(body))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitWhileStmt(*this);
  }
};
} // namespace jm
