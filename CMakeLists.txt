
cmake_minimum_required(VERSION 3.10)
project(MosaicDetective)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags for better optimization and warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic")

# Add the executable
add_executable(code code.cpp)

# Set output directory to current directory
set_target_properties(code PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
