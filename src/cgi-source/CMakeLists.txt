set(GET_SRC get.cpp)

SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

#将可执行文件存放到www/cgi-bin下
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/www/cgi-bin)
add_executable(get.cgi ${GET_SRC})

#set shared library for get.cgi
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(get.cgi searchEngine cgicc)
