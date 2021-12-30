cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 99)
add_library(libBigInt STATIC src/bigInt.c include/bigInt.h)
add_executable(untitled src/main.c src/bigInt.c include/bigInt.h)
add_executable(testExec test/test.c include/test.h)
target_link_libraries(untitled libBigInt)
target_link_libraries(testExec libBigInt)





