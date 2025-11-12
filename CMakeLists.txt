# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Name your project
project(RedisSync)

# Create the executable "app" from *all* source files
add_executable(app
    src/main.cpp
    src/utils.cpp
)

# Tell the compiler to look in the "include" directory for header files
# This adds the -I flag (e.g., -I/path/to/my_project/include)
target_include_directories(app PUBLIC include)