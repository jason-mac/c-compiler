#pragma once

#include <memory>
#include <vector>

#include "expressions/expr.hpp"
#include "statements/stmt.hpp"
#include "token.hpp"

namespace jm
{
struct Enumerator
{
  Token name;
  std::unique_ptr<Expr> value; // nullable
};

struct EnumDecl : Stmt
{
  Token name;
  std::vector<Enumerator> enumerators;

  EnumDecl(Token name, std::vector<Enumerator> enumerators)
      : name(std::move(name)), enumerators(std::move(enumerators))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitEnumDecl(*this);
  }
};
} // namespace jm
