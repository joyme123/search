#ifndef INVERTEDINDEXHASH_H
#define INVERTEDINDEXHASH_H
#include<iostream>
#include<string>
#include<memory>
#include"PostingList.h"

using namespace std;

class InvertedIndexHash{
public:
    unsigned int wordId;                 //单词编号
    shared_ptr<PostingList> postingList;   //指向包含该单词的倒排列表的指针
    unsigned long long docsCount;              //出现过该单词的文档数
    unsigned long long totalCount;             //在所有文档中该单词出现的次数和
};
#endif
