#ifndef FULLTEXTDOCUMENTCONTROLLER_H
#define FULLTEXTDOCUMENTCONTROLLER_H
#include <string>
#include "src/core/controller/AbstractDocumentController.h"
#include "src/core/dao/DocumentDAO.h"
#include "src/core/dao/WordDAO.h"
#include "src/core/util/WordSplitSingleton.h"
#include "src/core/util/FrequencyDictSingleton.h"
#include "src/core/util/StopWordDictSingleton.h"
#include "src/core/analysis/DocumentParser.h"
#include "src/core/analysis/DocumentAnalysis.h"
#include "src/core/analysis/SimHashCal.h"
#include "src/core/model/Document.h"
#include "src/core/model/Word.h"
#include "src/core/model/PostingList.h"

/**
 * 全文本索引，不会对文本作任何处理的入口,可以用来作为网站内部的全文搜索引擎
 * author:jiangpengfei 
 * date:2017-05-02
 */
class FullTextDocumentController:public AbstractDocumentController{
    public:
        int documentEntry(std::string documentStr);
};

#endif