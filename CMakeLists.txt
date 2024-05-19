cmake_minimum_required(VERSION 3.10)
project(lisp_compiler)

# Compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(lisp_compiler ${SOURCES})

# Include directories for header files
file(GLOB_RECURSE INCLUDES "src/*.h")
foreach(_include ${INCLUDES})
    get_filename_component(_include_dir ${_include} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${_include_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)
include_directories(${INCLUDE_DIRS})

