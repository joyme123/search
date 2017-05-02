/**
 * filename:WordController.h
 * 单词类的控制器
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include "src/core/db/ConnectionPool.h"
#include "src/core/dao/WordDAO.h"

class WordController{
	private:
		ConnectionPool* pool = ConnectionPool::createConnectionPool(100);
public:
	InvertedIndexHash searchWord(std::string word);

};
#endif