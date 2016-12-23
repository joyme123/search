#include "WordController.h"

InvertedIndexHash WordController::searchWord(std::string word){
	Mysql mysql = this->pool->getConnection();
	WordDAO wordDao(&mysql);
	InvertedIndexHash invertedIndexHash = wordDao.searchWord(word);
	this->pool->retConnection(mysql);
	return invertedIndexHash;
}