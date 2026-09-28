#pragma once

namespace jm
{
class BinaryExpr;
class UnaryExpr;
class LiteralExpr;
class NameExpr;
class CallExpr;
class IndexExpr;
class FieldExpr;
class CastExpr;
class SizeofExpr;
class ConditionalExpr;
class CommaExpr;
class AssignExpr;

class ExpressionStmt;
class BlockStmt;
class IfStmt;
class WhileStmt;
class DoWhileStmt;
class ForStmt;
class BreakStmt;
class ContinueStmt;
class ReturnStmt;
class VarDeclStmt;
class FunctionDecl;
class StructDecl;
class EnumDecl;

class ExprVisitor
{
public:
  virtual ~ExprVisitor() = default;
  virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
  virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
  virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
  virtual void visitNameExpr(NameExpr& expr) = 0;
  virtual void visitCallExpr(CallExpr& expr) = 0;
  virtual void visitIndexExpr(IndexExpr& expr) = 0;
  virtual void visitFieldExpr(FieldExpr& expr) = 0;
  virtual void visitCastExpr(CastExpr& expr) = 0;
  virtual void visitSizeofExpr(SizeofExpr& expr) = 0;
  virtual void visitConditionalExpr(ConditionalExpr& expr) = 0;
  virtual void visitCommaExpr(CommaExpr& expr) = 0;
  virtual void visitAssignExpr(AssignExpr& expr) = 0;
};

class StmtVisitor
{
public:
  virtual ~StmtVisitor() = default;
  virtual void visitExpressionStmt(ExpressionStmt& stmt) = 0;
  virtual void visitBlockStmt(BlockStmt& stmt) = 0;
  virtual void visitIfStmt(IfStmt& stmt) = 0;
  virtual void visitWhileStmt(WhileStmt& stmt) = 0;
  virtual void visitDoWhileStmt(DoWhileStmt& stmt) = 0;
  virtual void visitForStmt(ForStmt& stmt) = 0;
  virtual void visitBreakStmt(BreakStmt& stmt) = 0;
  virtual void visitContinueStmt(ContinueStmt& stmt) = 0;
  virtual void visitReturnStmt(ReturnStmt& stmt) = 0;
  virtual void visitVarDeclStmt(VarDeclStmt& stmt) = 0;
  virtual void visitFunctionDecl(FunctionDecl& stmt) = 0;
  virtual void visitStructDecl(StructDecl& stmt) = 0;
  virtual void visitEnumDecl(EnumDecl& stmt) = 0;
};
} // namespace jm
