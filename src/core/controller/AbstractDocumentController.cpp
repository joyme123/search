/**
 * filename:DocumentController.cpp
 * document controller
 * insert document by this class,it will spilt document into words,
 * and then store them
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"src/core/controller/AbstractDocumentController.h"

std::vector< Document > AbstractDocumentController::searchDocument(std::vector< unsigned int > documentId)
{
    Mysql mysql = this->pool->getConnection();
	DocumentDAO documentDao(&mysql);

	std::vector<Document> docs = documentDao.searchDocument(documentId);
    this->pool->retConnection(mysql);
    return docs;
}


