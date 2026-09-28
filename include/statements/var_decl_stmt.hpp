#pragma once

#include <memory>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"
#include "token.hpp"
#include "type.hpp"

namespace jm
{
struct VarDeclStmt : Stmt
{
  Type type;
  Token name;
  std::unique_ptr<Expr> initializer; // nullable

  VarDeclStmt(Type type, Token name, std::unique_ptr<Expr> initializer)
      : type(std::move(type)), name(std::move(name)), initializer(std::move(initializer))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitVarDeclStmt(*this);
  }
};
} // namespace jm
