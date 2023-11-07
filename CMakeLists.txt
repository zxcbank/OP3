cmake_minimum_required(VERSION 3.26)
project(labwork3_zxcbank)

set(CMAKE_CXX_STANDARD 17)

add_executable(labwork3_zxcbank main.cpp
        Parser.cpp
        Parser.h
        Pile.cpp
        Pile.h
        image.cpp
        image.h)
