cmake_minimum_required(VERSION 3.20.0)

set (SRC jasonobject.h jasonobject.cpp jasonvalue.h jasonvalue.cpp main.cpp)
add_executable(test ${SRC})