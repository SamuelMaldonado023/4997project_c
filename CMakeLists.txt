cmake_minimum_required(VERSION 3.10)

project(SearchEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# All source files
set(SOURCES
    main.cpp
    ParsedFile.cpp
    InvertedIndex.cpp
)

add_executable(search_engine ${SOURCES})
