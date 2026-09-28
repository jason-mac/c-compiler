#pragma once

#include "token.hpp"

namespace jm
{
// Minimal placeholder type representation: a base type name (e.g. int, char,
// or a struct/typedef identifier) plus a pointer depth (0 = not a pointer).
// Doesn't yet cover arrays, function pointers, or qualifiers.
struct Type
{
  Token name;
  int pointerDepth = 0;
};
} // namespace jm
