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

std::vector<Document> WordController::searchWithSentence(std::string& sentence,int& docCount,int pageIndex,int pageSize){
	//获取分词的实例
	WordSplitSingleton* wordSplit = WordSplitSingleton::getInstance(__FRISO_COMPLEX_MODE__);
	//得到分词结果
	std::map< std::string, std::vector< int > > wordMap = wordSplit->splitWord(sentence);
	//用来保存结果,表示某个文章id出现的次数
	std::map<int,int> result;

	//分词
	std::string word;
	//对map进行循环操作,
	for(std::map<std::string,std::vector<int> >::iterator it = wordMap.begin(); it != wordMap.end(); it++){
		word = it->first;
		InvertedIndexHash hash = this->searchWord(word);
		std::shared_ptr<PostingList> list = hash.postingList;
		while(list != NULL){
			if(result.find(list->documentId) != result.end()){
				result[list->documentId]++;
			}else{
				result[list->documentId] = 1;
			}
			list = list->next;
		}
	}

	std::vector<std::pair<int,int> > sorting; 
	//将map中的元素保存到vector中进行排序
	for(auto it = result.begin(); it != result.end(); it++){
		sorting.push_back(*it);
	}

	std::sort(sorting.begin(),sorting.end(),[](const std::pair<int,int>& l,const std::pair<int,int>& r){
		return l.second > r.second;
	});

	docCount = sorting.size();

	int offset = (pageIndex - 1) * pageSize;
	//保存最后要查询的文档id
	std::vector<unsigned int> ids;
	for(unsigned int i = offset; i < offset + pageSize && i < sorting.size(); i++){
		ids.push_back(sorting[i].first);
	}
	
	FullTextDocumentController hd;
	std::vector<Document> docs =  hd.searchDocument(ids);

	
	return docs;
}