# c-compiler

A C compiler, built through LLVM/MLIR, in C++.

## Status

Early scaffolding — build system and project layout only, no frontend/codegen yet.

## Building

```sh
cmake -S . -B build
cmake --build build
```

## Layout

```
src/       source files
include/   headers
tests/     tests
```

## Requirements

- CMake 3.20+
- A C++23 compiler
- LLVM/MLIR (not wired up yet)
