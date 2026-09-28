#pragma once

#include "visitor.hpp"

namespace jm
{
class Stmt
{
public:
  virtual ~Stmt() = default;
  virtual void accept(StmtVisitor& visitor) = 0;
};
} // namespace jm
