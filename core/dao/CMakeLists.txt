#place dao library into lib folder
set(LIB_SRC DocumentDAO.cpp WordDAO.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library (dao SHARED ${LIB_SRC})
add_library(dao_static STATIC ${LIB_SRC})


#link library
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(dao libmysqlcppconn.so util model glog)
target_link_libraries(dao_static libmysqlcppconn.so util model glog)

set_target_properties(dao PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(dao PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(dao_static PROPERTIES OUTPUT_NAME "dao")
set_target_properties(dao_static PROPERTIES CLEAN_DIRECT_OUT 1)

