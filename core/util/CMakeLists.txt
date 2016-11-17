cmake_minimum_required(VERSION 2.6)
#place document parser shared library into lib directory
set(LIB_SRC DocumentParser.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library (documentParser SHARED ${LIB_SRC})
add_library(documentParser_static STATIC ${LIB_SRC})
set_target_properties(documentParser PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(documentParser PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(documentParser_static PROPERTIES OUTPUT_NAME "documentParser")
set_target_properties(documentParser_static PROPERTIES CLEAN_DIRECT_OUT 1)

#set friso.so for document parser
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(documentParser friso)
target_link_libraries(documentParser_static friso)

INSTALL(TARGETS documentParser documentParser_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
INSTALL(FILES DocumentParser.h DESTINATION include/documentParser)
