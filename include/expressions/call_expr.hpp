#pragma once

#include <memory>
#include <vector>

#include "expressions/expr.hpp"
#include "token.hpp"

namespace jm
{
struct CallExpr : Expr
{
  std::unique_ptr<Expr> callee;
  Token paren;
  std::vector<std::unique_ptr<Expr>> arguments;

  CallExpr(std::unique_ptr<Expr> callee, Token paren, std::vector<std::unique_ptr<Expr>> arguments)
      : callee(std::move(callee)), paren(std::move(paren)), arguments(std::move(arguments))
  {
  }

  void accept(ExprVisitor& visitor) override
  {
    visitor.visitCallExpr(*this);
  }
};
} // namespace jm
