#place searchEngine library into lib folder
set(LIB_SRC ConnectionPool.cpp
            DocumentDAO.cpp
            WordDAO.cpp 
            DocumentController.cpp 
            WordController.cpp 
            Mysql.cpp
            InvertedIndexHash.cpp 
            PostingList.cpp 
            Word.cpp 
            Document.cpp 
            Package.cpp 
            SimHash.cpp
            util/DocumentParser.cpp 
            util/util.cpp 
            util/config.cpp 
            util/SocketStreamParser.cpp 
            util/DocumentAnalysis.cpp 
            util/SimHashCal.cpp 
            util/FrequencyDictSingleton.cpp 
            util/StopWordDictSingleton.cpp
            util/WordSplitSingleton.cpp
            util/ResourceManage.cpp)
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

