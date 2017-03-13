cmake_minimum_required(VERSION 2.6)
project(search)
add_definitions(-std=c++11)
add_subdirectory(include/friso)
add_subdirectory(include/socket)
add_subdirectory(include/cityHash)
add_subdirectory(core)
add_subdirectory(test bin)
add_subdirectory(test/friso)
add_subdirectory(www/cgi-source)

SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  


#document entry,generate index for search engine
#set(FORMATEDDOCENTRY_SRC formatedDocumentEntry.cpp)
set(DOCENTRY_SRC documentEntry.cpp)
add_executable(documentEntry ${DOCENTRY_SRC})
#placePROJECT_SOURCE_DIR executable file 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#set shared library
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(documentEntry searchEngine socket)