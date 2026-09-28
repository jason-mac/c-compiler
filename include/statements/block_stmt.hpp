#pragma once

#include <memory>
#include <vector>

#include "statements/stmt.hpp"

namespace jm
{
struct BlockStmt : Stmt
{
  std::vector<std::unique_ptr<Stmt>> statements;

  BlockStmt(std::vector<std::unique_ptr<Stmt>> statements) : statements(std::move(statements)) {}

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitBlockStmt(*this);
  }
};
} // namespace jm
