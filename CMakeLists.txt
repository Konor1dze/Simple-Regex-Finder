cmake_minimum_required(VERSION 4.2)
project(SimpleRegexFinder)

set(CMAKE_CXX_STANDARD 20)

add_executable(SimpleRegexFinder main.cpp
        headers/readFile.h
        source/readFile.cpp
        source/listWorkingDirectory.cpp
        headers/listWorkingDirectory.h
        source/countLinesInBlock.cpp
        headers/countLinesInBlock.h
)