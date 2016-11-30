cmake_minimum_required(VERSION 2.6)
project(search)
add_definitions(-std=c++11)
add_subdirectory(include/friso)
add_subdirectory(core)
add_subdirectory(test bin)
add_subdirectory(test/friso)
add_subdirectory(www/cgi-source)
#client for this program
set(MAIN_SRC main.cpp)
#placePROJECT_SOURCE_DIR executable file 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(client ${MAIN_SRC})

#set shared library for connectTest and mysqlTest and ngramTest
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(client searchEngine)