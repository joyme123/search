#ifndef WORDDAO_H
#define WORDDAO_H

#include<iostream>
#include<string>

#include<glog/logging.h>

#include"Mysql.h"
#include"Word.h"
#include"InvertedIndexHash.h"
#include"PostingList.h"
#include"util/util.h"
#include"util/config.h"


class WordDAO{
private:
    std::string NGRAMTABLE = "ngramWord";		//通过ngram生成的词汇表
	std::string SPLITTABLE = "splitWord";				//通过分词生成的词汇表
public:
	WordDAO();
    /**
     * insert the word and it's postingList
     * @param word add word into database with it InvertedIndexHash
     * @param postingList word postingList
	 * @param totalCount word count
     * @return the added record id
     */
    int addWord(Word word,std::shared_ptr<PostingList>  postingList);
    
    /**
     * delete a record of the word by id
     * @param id word id
     * @return  affect rows num
     */
    
    int deleteWord(unsigned int id,InvertHashIndexType type);
    
    /**
     * update a word's InvertedIndexHash
     * @param id the word id
     * @param indexHash InvertedIndexHash of the word
     * @return affect rows
     */
    int updateWordInvertHash(unsigned int id,InvertedIndexHash indexHash);       
};

#endif
