cmake_minimum_required(VERSION 3.10)

project(4997project_c)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(main main.cpp)

# Link filesystem library (required for some compilers)
target_link_libraries(main stdc++fs)
