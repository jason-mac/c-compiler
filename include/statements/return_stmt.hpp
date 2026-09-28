#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"
#include "token.hpp"

namespace jm
{
struct ReturnStmt : Stmt
{
  Token keyword;
  std::unique_ptr<Expr> value;

  ReturnStmt(Token keyword, std::unique_ptr<Expr> value)
      : keyword(std::move(keyword)), value(std::move(value))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitReturnStmt(*this);
  }
};
} // namespace jm
