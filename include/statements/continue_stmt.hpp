#pragma once

#include "statements/stmt.hpp"
#include "token.hpp"

namespace jm
{
struct ContinueStmt : Stmt
{
  Token keyword;

  ContinueStmt(Token keyword) : keyword(std::move(keyword)) {}

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitContinueStmt(*this);
  }
};
} // namespace jm
