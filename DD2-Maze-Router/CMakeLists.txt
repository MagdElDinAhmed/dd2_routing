cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DD2-Maze-Router)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(DD2-Maze-Router 
    DD2-Maze-Router.cpp 
    TextParser.cpp
    Net.cpp
    Cell.cpp
)

# Include directories
target_include_directories(DD2-Maze-Router PUBLIC "${PROJECT_SOURCE_DIR}")
