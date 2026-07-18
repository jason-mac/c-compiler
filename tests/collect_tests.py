#!/usr/bin/env python3
# Scans this directory recursively for test_*.cpp files and prints them as
# a CMake list (semicolon-separated) on stdout, relative to this directory.

import pathlib

tests_dir = pathlib.Path(__file__).parent
sources = sorted(
    str(p.relative_to(tests_dir)) for p in tests_dir.rglob("test_*.cpp")
)

print(";".join(sources))
