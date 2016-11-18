cmake_minimum_required(VERSION 2.6)
#place document parser shared library into lib directory
set(LIB_SRC DocumentParser.cpp util.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library (util SHARED ${LIB_SRC})
add_library(util_static STATIC ${LIB_SRC})
set_target_properties(util PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(util PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(util PROPERTIES OUTPUT_NAME "util")
set_target_properties(util PROPERTIES CLEAN_DIRECT_OUT 1)

#set friso.so for document parser
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(util friso)
target_link_libraries(util friso)

#INSTALL(TARGETS util util_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
#INSTALL(FILES DocumentParser.h DESTINATION include/documentParser)
