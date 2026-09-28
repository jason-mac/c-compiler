#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"

namespace jm
{
struct IfStmt : Stmt
{
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> thenBranch;
  std::unique_ptr<Stmt> elseBranch;

  IfStmt(std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> thenBranch,
         std::unique_ptr<Stmt> elseBranch)
      : condition(std::move(condition)), thenBranch(std::move(thenBranch)),
        elseBranch(std::move(elseBranch))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitIfStmt(*this);
  }
};
} // namespace jm
