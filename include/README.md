# AST scaffolding notes

Every node type below is a data-only `struct` with an `accept(Visitor&)` for the visitor pattern (see `visitor.hpp`). None of `Parser::parse()`'s actual grammar logic exists yet, this is just the node vocabulary it'll build.

## Ported from lua-vm (adapted to C)

Expressions: `BinaryExpr`, `UnaryExpr`, `LiteralExpr`, `NameExpr`, `CallExpr`, `IndexExpr`, `FieldExpr` (added an `op` field to distinguish `.` vs `->`, which Lua doesn't need).

Statements: `ExpressionStmt`, `BlockStmt`, `IfStmt`, `WhileStmt`, `BreakStmt`, `ReturnStmt`, plus `DoWhileStmt` (adapted from lua-vm's `RepeatStmt`, opposite loop polarity: C loops *while* true, Lua's `repeat` loops *until* true) and `ContinueStmt` (new, C has `continue` and Lua doesn't).

## Deliberately not ported

- **`FunctionExpr`** — Lua has function literals/closures; C doesn't, so there's nothing to port.
- **`ForEachStmt` / `ForRangeStmt`** — Lua's `for` shapes don't match C's `for (init; cond; incr)`. Built C's own `ForStmt` instead (see below).
- **`FunctionStmt` / `LocalFunctionStmt`** — Lua's function statement is just `function name() ... end`. Built C's own `FunctionDecl` instead (see below).
- **`AssignStmt`** — in the C grammar, assignment is an `assignment-expression`, not its own statement. Built `AssignExpr` instead.

## Designed for C, not from lua-vm

- **`type.hpp` / `Type`** — minimal placeholder: a base type name token + a pointer-depth int (`int` = 0, `int *` = 1, ...). Doesn't cover arrays, function pointers, or qualifiers (`const`/`volatile`) yet.
- **`ForStmt`** — `init` (nullable `Stmt`) / `condition` (nullable `Expr`) / `increment` (nullable `Expr`) / `body`.
- **`VarDeclStmt`** — `Type` + name + optional initializer. Covers both locals and (reused as-is) globals.
- **`FunctionDecl`** — return `Type`, name, `std::vector<Param>` (each a `Type` + name), and a nullable body (`nullptr` body = prototype, no definition).
- **`StructDecl`** — name + `std::vector<StructField>` (each a `Type` + name). No unions yet, structurally identical so trivial to add later.
- **`EnumDecl`** — name + `std::vector<Enumerator>` (name + optional constant-expression value).
- **`CastExpr`** — `Type` + the expr being cast.
- **`SizeofExpr`** — holds either an `expr` (for `sizeof expr`) or a `std::optional<Type>` (for `sizeof(type)`).
- **`ConditionalExpr`** — the ternary `a ? b : c`.
- **`CommaExpr`** — `std::vector<Expr>`, the comma operator (`a, b, c`), lowest-precedence production in the grammar.
- **`AssignExpr`** — target + operator token (`=`, `+=`, ...) + value.

## Not designed yet, worth considering

- **Union support** — `StructDecl`/`StructField` would need a union variant, or a shared base.
- **`typedef`** — not modeled at all; `typedef int MyInt;` has no node type.
- **Arrays and function pointers** — `Type` doesn't express either.
- **Typedef-name disambiguation** — C's classic parsing wrinkle: the parser needs a symbol table during parsing to know whether an identifier is a type name or a variable name (`x * y;` parses differently depending on whether `x` is a typedef). Not addressed by anything here, and it's a real parser-logic problem, not just a missing node type.
