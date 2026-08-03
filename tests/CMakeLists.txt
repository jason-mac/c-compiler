find_package(Python3 REQUIRED COMPONENTS Interpreter)

execute_process(
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/collect_tests.py
  OUTPUT_VARIABLE TEST_SOURCES
  OUTPUT_STRIP_TRAILING_WHITESPACE)

add_executable(ccompiler_tests ${TEST_SOURCES} ${PROJECT_SOURCE_DIR}/src/lexer.cpp
                               ${PROJECT_SOURCE_DIR}/src/parser.cpp)
target_include_directories(ccompiler_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ccompiler_tests PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ccompiler_tests)
