set(TESTNGRAM_SRC ngramTest.cpp)
set(TESTCONNECT_SRC connect.cpp)
set(TESTMSYQL_SRC mysqlTest.cpp)
set(TESTFRISO_SRC frisoTest.cpp)
#place executable file into test directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/bin)
add_executable(connectTest ${TESTCONNECT_SRC})
add_executable(mysqlTest ${TESTMSYQL_SRC})
add_executable(ngramTest ${TESTNGRAM_SRC})
add_executable(frisoTestC ${TESTFRISO_SRC})

#set shared library for connectTest and mysqlTest and ngramTest
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(connectTest libmysqlcppconn.so)
target_link_libraries(mysqlTest libmysqlcppconn.so)
target_link_libraries(ngramTest searchEngine)
target_link_libraries(frisoTestC searchEngine)
