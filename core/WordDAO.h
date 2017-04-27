/**
 * filename:WordDAO.h
 * 单词查询类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef WORDDAO_H
#define WORDDAO_H

#include<iostream>
#include<string>

#include<glog/logging.h>

#include"exception/TimeoutException.h"
#include"Mysql.h"
#include"Word.h"
#include"InvertedIndexHash.h"
#include"PostingList.h"
#include"util/util.h"
#include"util/config.h"


class WordDAO{
private:
    std::string TABLE = "word";
    std::string NGRAMTABLE = "ngramWord";		//通过ngram生成的词汇表
	std::string SPLITTABLE = "splitWord";				//通过分词生成的词汇表
    Mysql* mysql;
public:
	WordDAO(Mysql* mysql);
    /**
     * insert the word and it's postingList
     * @param word add word into database with it InvertedIndexHash
     * @param postingList word postingList
     * @return the added record id
     */
    int addWord(Word word,std::shared_ptr<PostingList>  postingList);
    
    /**
     * 添加或者更新一个单词，利用的是sql的ON DUPLICATE KEY UPDATE的语法
     * @param 要添加的单词
     * @param 要添加的单词对应的倒排索引
     * @return int 添加的单词id或者更新的数据数
     */
    int addOrUpdateWord(Word word,std::shared_ptr<PostingList>  postingList);

    /**
     * delete a record of the word by id
     * @param id word id
     * @return  affect rows num
     */
    
    int deleteWord(unsigned int id,InvertHashIndexType type);
    
    /**
     * update a word's InvertedIndexHash
     * @param id the word id
     * @param postingList postingList of the word
     * @return affect rows
     */
    int updateWord(unsigned int id,std::shared_ptr<PostingList> postingList);       
    
    /**
     * check if the word exist
     * @param word the word which need check
     * @return if exist,return the word id  else return -1
     */
    int isWordExist(std::string word);
    
    
    /**
     * search a word 
     * @param word the word need search
     * @return the word InvertedIndexHash
     */
    InvertedIndexHash searchWord(std::string word);
    
};

#endif
