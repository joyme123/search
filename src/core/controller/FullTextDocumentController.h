#include <string>
#include "src/core/controller/AbstractDocumentController.h"

/**
 * 全文本索引，不会对文本作任何处理的入口
 * author:jiangpengfei 
 * date:2017-05-02
 */
class FullTextDocumentController:public AbstractDocumentController{
    public:
        int documentEntry(std::string documentStr);
};