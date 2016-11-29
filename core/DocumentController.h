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
#include"Document.h"
#include"DocumentDAO.h"
#include"Word.h"
#include"WordDAO.h"

class DocumentController{
public:
    
    /**
     * input a format document string like title|type|author|url|text
     * @param documentFormat a format string
     * @return the word insert into database
     */
    int documentEntry(std::wstring documentFormat);
	
	std::vector< Document > searchDocument(std::vector<unsigned int > documentId);
    
};

#endif
