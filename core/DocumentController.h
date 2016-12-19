/**
 * document controller
 * insert document by this class,it will spilt document into words,
 * and then store them
 */

#ifndef DOCUMENTCONTROLLER_H
#define DOCUMENTCONTROLLER_H

#include<iostream>
#include<string>
#include<glog/logging.h>


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
public:
    
    /**
     * input a format document string like title|type|author|url|text
     * @param formatedDocument a format string
     * @return the words　count insert into database
     */
    int formatedDocumentEntry(std::string formatedDocument);

    /**
     * 原生文档的入口，比如通过爬虫刚下载下来的未处理的网页
     * @param documentStr document string content
     * @return 插入到数据库的单词的数量
     */
    int documentEntry(std::vector<Package> packs);
	
	std::vector< Document > searchDocument(std::vector<unsigned int > documentId);
    
};

#endif
