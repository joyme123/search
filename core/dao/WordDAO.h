#ifndef WORDDAO_H
#define WORDDAO_H

#include<iostream>
#include<string>
#include"../model/Word.h"
#include"../model/InvertedIndexHash.h"
#include"Mysql.h"
#include"../util/util.h"

class WordDAO{
private:
    string TABLE = "word";
public:
    /**
     * insert the word and it's InvertedIndexHash
     * @param word add word into database with it InvertedIndexHash
     * @param indexHash InvertedIndexHash of word
     * @return the added record id
     */
    int addWord(Word word,InvertedIndexHash indexHash);
    
    /**
     * delete a record of the word by id
     * @param id word id
     * @return  affect rows num
     */
    
    int deleteWord(unsigned int id);
    
    /**
     * update a word's InvertedIndexHash
     * @param id the word id
     * @param indexHash InvertedIndexHash of the word
     * @return affect rows
     */
    int updateWordInvertHash(unsigned int id,InvertedIndexHash indexHash);       
}

#endif
