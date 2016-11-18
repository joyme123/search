#place dao library into lib folder
set(LIB_SRC Document.cpp Word.cpp InvertedIndexHash.cpp PostingList.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library (model SHARED ${LIB_SRC})
add_library(model_static STATIC ${LIB_SRC})

set_target_properties(model PROPERTIES CLEAN_DIRECT_OUT 1)
set_target_properties(model PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(model_static PROPERTIES OUTPUT_NAME "model")
set_target_properties(model_static PROPERTIES CLEAN_DIRECT_OUT 1)

