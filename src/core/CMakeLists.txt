#place searchEngine library into lib folder
set(LIB_SRC db/ConnectionPool.cpp
            db/Mysql.cpp
            db/ResourceManage.cpp
            dao/DocumentDAO.cpp
            dao/WordDAO.cpp 
            controller/WordController.cpp
            controller/AbstractDocumentController.cpp
            controller/FullTextDocumentController.cpp
            controller/HtmlDocumentController.cpp 
            model/InvertedIndexHash.cpp 
            model/PostingList.cpp 
            model/Word.cpp 
            model/Document.cpp 
            model/SimHash.cpp
            model/Keyword.cpp
            analysis/DocumentParser.cpp 
            analysis/DocumentAnalysis.cpp 
            analysis/SimHashCal.cpp 
            util/util.cpp 
            util/config.cpp 
            util/FrequencyDictSingleton.cpp 
            util/StopWordDictSingleton.cpp 
            util/WordSplitSingleton.cpp 
            util/ConfigReader.cpp 
            util/Trie.cpp
            util/SortedHeap.hpp
            util/Timer.cpp
            util/FCgiIO.cpp
            )

SET(CMAKE_BUILD_TYPE Release)  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  
set(CMAKE_EXE_LINKER_FLAGS "-static")

#存放编译好的链接库
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#存放可执行文件路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#链接库的位置
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_library (searchEngine SHARED ${LIB_SRC})
add_library (searchEngine_static STATIC ${LIB_SRC})

target_link_libraries(searchEngine mysqlcppconn glog friso socket cityHash mongocxx bsoncxx pthread cpp_redis tacopie cgicc fcgi fcgi++)
target_link_libraries(searchEngine_static mysqlcppconn  glog friso socket cityHash mongocxx bsoncxx pthread cpp_redis tacopie cgicc fcgi fcgi++)


set_target_properties(searchEngine PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(searchEngine PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(searchEngine_static PROPERTIES OUTPUT_NAME "searchEngine")
set_target_properties(searchEngine_static PROPERTIES CLEAN_DIRECT_OUT 1)

# 生成需要执行的文件
set(DOCHTMLPROCESS_SRC exe/htmlProcess.cpp)
set(DOCFULLTEXTPROCESS_SRC exe/fullTextProcess.cpp)
set(INITSQL_SRC exe/initSql.cpp)
set(Get_SRC exe/get_fastcgi.cpp)
set(Suggestion_SRC exe/suggestion.cpp)

add_executable(htmlProcess ${DOCHTMLPROCESS_SRC})
add_executable(fullTextProcess ${DOCFULLTEXTPROCESS_SRC})
add_executable(initSql ${INITSQL_SRC})
add_executable(get.fcgi ${Get_SRC})
add_executable(suggestion.fcgi ${Suggestion_SRC})

# SET_TARGET_PROPERTIES (htmlProcess PROPERTIES LINK_SEARCH_START_STATIC 1)
# SET_TARGET_PROPERTIES (htmlProcess PROPERTIES LINK_SEARCH_END_STATIC 1)

# mysqlcppconn.a  glog.a friso.a socket.a cityHash.a  bsoncxx.a mongocxx.a pthread.a tacopie.a  cpp_redis.a
target_link_libraries(htmlProcess searchEngine.a
                                  libmysqlcppconn-static.a  
                                  libmysqlclient.a
                                  dl 
                                  glog.a 
                                  friso.a 
                                  socket.a 
                                  cityHash.a  
                                  mongocxx.a 
                                  libmongoc-1.0.a
                                  libbsoncxx.a 
                                  libbson.a 
                                  pthread
                                  cpp_redis.a  
                                  tacopie.a  
                                  z 
                                  rt
                                  ssl.a
                                  crypto.a
                                  )
target_link_libraries(fullTextProcess searchEngine.a
                                  libmysqlcppconn-static.a  
                                  libmysqlclient.a
                                  dl 
                                  glog.a 
                                  friso.a 
                                  socket.a 
                                  cityHash.a
                                  mongocxx.a 
                                  libmongoc-1.0.a 
                                  libbsoncxx.a 
                                  libbson.a 
                                  pthread
                                  cpp_redis.a  
                                  tacopie.a  
                                  z 
                                  rt
                                  ssl.a
                                  crypto.a
                                  )
target_link_libraries(initSql     searchEngine.a
                                  libmysqlcppconn-static.a  
                                  libmysqlclient.a
                                  dl 
                                  glog.a 
                                  friso.a 
                                  socket.a 
                                  cityHash.a  
                                  mongocxx.a 
                                  libmongoc-1.0.a
                                  libbsoncxx.a 
                                  libbson.a 
                                  pthread
                                  cpp_redis.a  
                                  tacopie.a  
                                  z 
                                  rt
                                  ssl.a
                                  crypto.a
                                   )

target_link_libraries(get.fcgi     searchEngine.a
                                  libmysqlcppconn-static.a  
                                  libmysqlclient.a
                                  dl 
                                  glog.a 
                                  friso.a 
                                  socket.a 
                                  cityHash.a  
                                  mongocxx.a 
                                  libmongoc-1.0.a
                                  libbsoncxx.a 
                                  libbson.a 
                                  pthread
                                  cpp_redis.a  
                                  tacopie.a  
                                  z 
                                  rt
                                  ssl.a
                                  crypto.a
                                  libcgicc.a
                                  libfcgi.a
                                  libfcgi++.a
                                   )

target_link_libraries(suggestion.fcgi     searchEngine.a
                                  libmysqlcppconn-static.a  
                                  libmysqlclient.a
                                  dl 
                                  glog.a 
                                  friso.a 
                                  socket.a 
                                  cityHash.a  
                                  mongocxx.a 
                                  libmongoc-1.0.a
                                  libbsoncxx.a 
                                  libbson.a 
                                  pthread
                                  cpp_redis.a  
                                  tacopie.a  
                                  z 
                                  rt
                                  ssl.a
                                  crypto.a
                                  libcgicc.a
                                  libfcgi.a
                                  libfcgi++.a
                                   )