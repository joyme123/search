#ifndef _DOCUMENTDAO_H
#define _DOCUMENTDAO_H

#include<iostream>
#include<string>
#include<glog/logging.h>
#include"Mysql.h"
#include"Document.h"
#include"util/util.h"

class DocumentDAO:public Mysql{
    private:
    std::string TABLE = "document";
    public:
		DocumentDAO();
        
        /**
         * insert a docuemnt into database and return id of this
         * @param document add document into database(maybe use fastfs to storage)
         * @return id of this document
         */
        int addDocument(Document document); 
        
        /**
         * delete the document with an id
         * @param id document id
         * @return affect rows count
         */
        int deleteDocument(unsigned int id);   
        
        /**
         * parse the docment the put words of this document into database
         * each word generate a record reference document id
         * @param document the document to parse
         * @return affect rows count
         */
        int parseDocumentAndUpdate(Document document); 
		
		/**
		 * search specific document with some document id
		 * @param documentId document id
		 * @return vector with Document
		 */
		std::vector<Document> searchDocument(std::vector<unsigned int> documentId);
};

#endif
