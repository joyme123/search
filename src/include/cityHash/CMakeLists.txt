#place cityHash library into lib folder
set(LIB_SRC city.cc)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

add_library (cityHash SHARED ${LIB_SRC})
add_library(cityHash_static STATIC ${LIB_SRC})


#link library
link_directories(${PROJECT_SOURCE_DIR}/lib)

set_target_properties(cityHash PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(cityHash PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(cityHash_static PROPERTIES OUTPUT_NAME "cityHash")
set_target_properties(cityHash_static PROPERTIES CLEAN_DIRECT_OUT 1)

