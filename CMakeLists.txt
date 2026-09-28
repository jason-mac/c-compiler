cmake_minimum_required(VERSION 3.20)
project(c-compiler LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)
find_package(GTest REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Found MLIR ${MLIR_PACKAGE_VERSION}")

add_executable(ccompiler src/main.cpp src/lexer.cpp src/parser.cpp)
target_include_directories(ccompiler PRIVATE include)
target_include_directories(ccompiler SYSTEM PRIVATE ${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS})
target_compile_definitions(ccompiler PRIVATE ${LLVM_DEFINITIONS})

target_link_libraries(ccompiler PRIVATE MLIRIR MLIRParser MLIRSupport)

enable_testing()
add_subdirectory(tests)
