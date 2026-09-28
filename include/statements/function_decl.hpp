#pragma once

#include <memory>
#include <vector>

#include "statements/stmt.hpp"
#include "token.hpp"
#include "type.hpp"

namespace jm
{
struct Param
{
  Type type;
  Token name;
};

struct FunctionDecl : Stmt
{
  Type returnType;
  Token name;
  std::vector<Param> params;
  std::unique_ptr<Stmt> body; // nullable: absent for a prototype (no body, just ';')

  FunctionDecl(Type returnType, Token name, std::vector<Param> params, std::unique_ptr<Stmt> body)
      : returnType(std::move(returnType)), name(std::move(name)), params(std::move(params)),
        body(std::move(body))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitFunctionDecl(*this);
  }
};
} // namespace jm
