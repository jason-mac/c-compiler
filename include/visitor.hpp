#pragma once

namespace jm
{
class Expr;
class Stmt;

class ExprVisitor
{
public:
  virtual ~ExprVisitor() = default;
};

class StmtVisitor
{
public:
  virtual ~StmtVisitor() = default;
};
} // namespace jm
