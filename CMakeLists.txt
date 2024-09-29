cmake_minimum_required(VERSION 3.10)
project(lisp_compiler)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Add the source files
add_executable(lisp_compiler
  src/lexer.cpp
  src/parser.cpp
  src/compiler.cpp
  src/main.cpp)

# Include directories for header files
target_include_directories(lisp_compiler PRIVATE include)
