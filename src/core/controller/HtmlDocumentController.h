#include "src/core/controller/AbstractDocumentController.cpp"

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