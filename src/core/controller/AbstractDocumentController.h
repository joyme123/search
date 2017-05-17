/**
 * filename:DocumentController.h
 * document controller
 * insert document by this class,it will spilt document into words,
 * and then store them
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */

#ifndef ABSTRACTDOCUMENTCONTROLLER_H
#define ABSTRACTDOCUMENTCONTROLLER_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<glog/logging.h>

#include "src/core/db/ConnectionPool.h"
#include "src/core/dao/DocumentDAO.h"
#include "src/core/model/Document.h"

class AbstractDocumentController{
    private:
    protected:
        ConnectionPool* pool = ConnectionPool::createConnectionPool(100);
    public:

        /**
        * 文档入口
        * @param document 文档的内容
        * @return 插入到数据库的单词的数量
        */
        virtual int documentEntry(std::string document) = 0;
        
        /**
        * 搜索文档
        * @param documentId 文档id的向量数组
        * @return vector 搜索到的文档数组
        */
        std::vector< Document > searchDocument(std::vector<unsigned int > documentId);
    
};

#endif
