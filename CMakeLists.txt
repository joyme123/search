cmake_minimum_required(VERSION 2.6)
project(search)


SET(CMAKE_CXX_COMPILER "clang++")
SET(CMAKE_CXX_FLAGS "-std=c++11")
#SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Werror -Weverything -Wno-deprecated-declarations -Wno-disabled-macro-expansion -Wno-float-equal -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-missing-prototypes -Wno-padded -Wno-old-style-cast")
#SET(CMAKE_EXE_LINKER_FLAGS "-lc++ -lc++abi")
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
set(DOCPROCESS_SRC process.cpp)
add_executable(documentEntry ${DOCENTRY_SRC})
add_executable(process ${DOCPROCESS_SRC})
#placePROJECT_SOURCE_DIR executable file 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


#set shared library
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(documentEntry searchEngine socket)
target_link_libraries(process searchEngine)