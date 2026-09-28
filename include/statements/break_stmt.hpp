#pragma once

#include "statements/stmt.hpp"
#include "token.hpp"

namespace jm
{
struct BreakStmt : Stmt
{
  Token keyword;

  BreakStmt(Token keyword) : keyword(std::move(keyword)) {}

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitBreakStmt(*this);
  }
};
} // namespace jm
