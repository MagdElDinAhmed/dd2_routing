# CMakeList.txt : CMake project for DD2-Maze-Router, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (DD2-Maze-Router "DD2-Maze-Router.cpp" "DD2-Maze-Router.h" "TextParser.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DD2-Maze-Router PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
