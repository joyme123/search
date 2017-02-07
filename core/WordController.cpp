/**
 * filename:WordController.cpp
 * 单词类的控制器
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include "WordController.h"

InvertedIndexHash WordController::searchWord(std::string word){
	Mysql mysql = this->pool->getConnection();
	WordDAO wordDao(&mysql);
	InvertedIndexHash invertedIndexHash = wordDao.searchWord(word);
	this->pool->retConnection(mysql);
	return invertedIndexHash;
}