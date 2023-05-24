cmake_minimum_required(VERSION 3.25)
project(SearchingProgram)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SearchingProgram
        main.cpp
        Text.cpp
        Text.h
        Word.cpp
        Word.h
        )
