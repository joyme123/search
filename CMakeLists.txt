cmake_minimum_required(VERSION 2.6)
project(search)


SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "-std=c++11 -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 ")

#设置引用的文件路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})


add_subdirectory(src)
add_subdirectory(test)

SET(CMAKE_BUILD_TYPE Release)  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

#存放编译好的链接库
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#存放可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#链接库的位置
link_directories(${PROJECT_SOURCE_DIR}/lib)


