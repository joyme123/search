cmake_minimum_required(VERSION 2.6)
project(search)

add_executable(search main.cpp)

install(TARGETS search RUNTIME DESTINATION bin)
