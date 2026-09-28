#pragma once

#include "visitor.hpp"

namespace jm
{
class Expr
{
public:
  virtual ~Expr() = default;
  virtual void accept(ExprVisitor& visitor) = 0;
};
} // namespace jm
