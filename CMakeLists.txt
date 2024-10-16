# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(GridLex VERSION 1.0)

# Specify the C++ standard (you can adjust this if necessary)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(GridLex main.cpp gridsearch.cpp trie.cpp)

# Optionally, you can specify compiler flags
# Uncomment the line below if you want additional warnings
# target_compile_options(GridLex PRIVATE -Wall -Wextra)

# Include directories if you have any header files in a separate folder
# For example, if your headers are in an "include" folder, add this:
# target_include_directories(GridLex PUBLIC ${PROJECT_SOURCE_DIR}/include)
