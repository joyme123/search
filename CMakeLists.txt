cmake_minimum_required(VERSION 2.6)
project(search)

#add_subdirectory(core/util)
#add_subdirectory(core/dao)
#add_subdirectory(core/model)

add_executable(search main.cpp)

install(TARGETS search RUNTIME DESTINATION bin)
