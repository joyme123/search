#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include"WordDAO.h"
#include "ConnectionPool.h"

class WordController{
	private:
		ConnectionPool* pool = ConnectionPool::createConnectionPool(100);
public:
	InvertedIndexHash searchWord(std::string word);

};
#endif