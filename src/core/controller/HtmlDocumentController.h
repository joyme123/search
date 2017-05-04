#ifndef HTMLDOCUMENTCONTROLLER_H
#define HTMLDOCUMENTCONTROLLER_H
#include "src/core/controller/AbstractDocumentController.cpp"
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
 * DocumentController的派生类，负责从mongodb中取出网页内容处理
 *
 *
 *
 */
class HtmlDocumentController:public AbstractDocumentController{
    public:

        /**
        * 文档入口
        * @param document html文档的内容
        * @return 插入到数据库的单词的数量
        */
        int documentEntry(std::string document);
};

#endif