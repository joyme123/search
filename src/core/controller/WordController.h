/**
 * filename:WordController.h
 * 单词类的控制器
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "src/core/model/Document.h"
#include "src/core/db/ConnectionPool.h"
#include "src/core/dao/WordDAO.h"
#include "src/core/util/WordSplitSingleton.h"
#include "src/include/friso/friso.h"
#include "src/core/util/util.h"
#include "src/core/controller/FullTextDocumentController.h"

class WordController{
	private:
		ConnectionPool* pool = ConnectionPool::createConnectionPool(100);
	public:
		/**
		* 根据单词搜索到InvertedIndexHash
		* @param word 搜索的单词
		* @return InvertedIndexHash 单词索引的文档列表
		*/
		InvertedIndexHash searchWord(std::string word);

		/**
		* 接受长句子输入，内部分词并输出相关文档
		* @param sentence 搜索的句子
		* @param docCount 文档总数
		* @param pageIndex 页码
		* @param pageSize 页大小
		* @return vector 文档的数组
		*/
		std::vector<Document> searchWithSentence(std::string& sentence,int& docCount,int pageIndex,int pageSize);

};
#endif