cmake_minimum_required(VERSION 2.6)
project(ngramTest)
add_subdirectory(util)
aux_source_directory(. DIR_TEST_SRCS)

add_executable(ngramTest $(DIR_TEST_SRCS))
target_link_libraries(ngramTest DocumentParser)
