/**
 * filename:DocumentController.h
 * document controller
 * insert document by this class,it will spilt document into words,
 * and then store them
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */

#ifndef DOCUMENTCONTROLLER_H
#define DOCUMENTCONTROLLER_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<glog/logging.h>

#include "ConnectionPool.h"
#include"util/DocumentParser.h"
#include"util/DocumentAnalysis.h"
#include"util/SimHashCal.h"
#include"util/FrequencyDictSingleton.h"
#include"util/StopWordDictSingleton.h"
#include"Document.h"
#include"DocumentDAO.h"
#include"Word.h"
#include"WordDAO.h"
#include"PostingList.h"

class DocumentController{
    private:
        ConnectionPool* pool = ConnectionPool::createConnectionPool(100);
public:
    
    /**
     * input a format document string like title|type|author|url|text
     * @param formatedDocument a format string
     * @return the words　count insert into database
     */
    int formatedDocumentEntry(std::string formatedDocument);

    /**
     * 原生文档的入口，比如通过爬虫刚下载下来的未处理的网页，每个网页都被封装在package中
     * @param packs 原生网页的pack
     * @return 插入到数据库的单词的数量
     */
    int documentEntry(std::vector<Package> packs);
	
    /**
     * 搜索文档
     * @param documentId 文档id的向量数组
     * @return vector 搜索到的文档数组
     */
	std::vector< Document > searchDocument(std::vector<unsigned int > documentId);
    
};

#endif
