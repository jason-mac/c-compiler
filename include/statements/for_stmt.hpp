#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"

namespace jm
{
struct ForStmt : Stmt
{
  std::unique_ptr<Stmt> init;      // nullable
  std::unique_ptr<Expr> condition; // nullable
  std::unique_ptr<Expr> increment; // nullable
  std::unique_ptr<Stmt> body;

  ForStmt(std::unique_ptr<Stmt> init, std::unique_ptr<Expr> condition,
          std::unique_ptr<Expr> increment, std::unique_ptr<Stmt> body)
      : init(std::move(init)), condition(std::move(condition)), increment(std::move(increment)),
        body(std::move(body))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitForStmt(*this);
  }
};
} // namespace jm
