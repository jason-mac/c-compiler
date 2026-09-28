#pragma once

#include <vector>

#include "statements/stmt.hpp"
#include "token.hpp"
#include "type.hpp"

namespace jm
{
struct StructField
{
  Type type;
  Token name;
};

struct StructDecl : Stmt
{
  Token name;
  std::vector<StructField> fields;

  StructDecl(Token name, std::vector<StructField> fields)
      : name(std::move(name)), fields(std::move(fields))
  {
  }

  void accept(StmtVisitor& visitor) override
  {
    visitor.visitStructDecl(*this);
  }
};
} // namespace jm
