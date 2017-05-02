#place searchEngine library into lib folder
set(LIB_SRC db/ConnectionPool.cpp
            db/Mysql.cpp
            db/ResourceManage.cpp
            dao/DocumentDAO.cpp
            dao/WordDAO.cpp 
            controller/DocumentController.cpp 
            controller/WordController.cpp 
            model/InvertedIndexHash.cpp 
            model/PostingList.cpp 
            model/Word.cpp 
            model/Document.cpp 
            model/Package.cpp 
            model/SimHash.cpp
            analysis/DocumentParser.cpp 
            analysis/SocketStreamParser.cpp 
            analysis/DocumentAnalysis.cpp 
            analysis/SimHashCal.cpp 
            util/util.cpp 
            util/config.cpp 
            util/FrequencyDictSingleton.cpp 
            util/StopWordDictSingleton.cpp
            util/WordSplitSingleton.cpp
            )
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  

add_library (searchEngine SHARED ${LIB_SRC})
add_library(searchEngine_static STATIC ${LIB_SRC})


#link library
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(searchEngine libmysqlcppconn.so  glog friso socket cityHash libmongocxx.so libbsoncxx.so pthread cpp_redis tacopie )
target_link_libraries(searchEngine_static libmysqlcppconn.so  glog friso socket cityHash libmongocxx.so libbsoncxx.so pthread cpp_redis tacopie )


set_target_properties(searchEngine PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(searchEngine PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(searchEngine_static PROPERTIES OUTPUT_NAME "searchEngine")
set_target_properties(searchEngine_static PROPERTIES CLEAN_DIRECT_OUT 1)

set(DOCENTRY_SRC exe/documentEntry.cpp)
set(DOCPROCESS_SRC exe/process.cpp)
add_executable(documentEntry ${DOCENTRY_SRC})
add_executable(process ${DOCPROCESS_SRC})

#设置可执行文件的存放动态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(documentEntry searchEngine socket)
target_link_libraries(process searchEngine)