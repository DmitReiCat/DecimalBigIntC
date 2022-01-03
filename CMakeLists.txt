cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 99)
add_library(libBigInt STATIC src/bigInt.c)
add_executable(untitled src/main.c)
add_executable(testExec test/test.c)
target_link_libraries(untitled libBigInt)
target_link_libraries(testExec libBigInt)





