set(TESTFRISO_SRC tst-friso.cpp)
#place executable file into test directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/friso)
add_executable(frisoTest ${TESTFRISO_SRC}/test/friso/bin)

#set shared library for connectTest and mysqlTest and ngramTest
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(frisoTest friso)
