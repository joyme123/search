/**
 * filename:InvertedIndexHash.h
 * 文档倒排索引类的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef INVERTEDINDEXHASH_H
#define INVERTEDINDEXHASH_H
#include <iostream>
#include <string>
#include <memory>
#include "src/core/model/PostingList.h"
#include "src/core/util/config.h"

class InvertedIndexHash{
public:
    unsigned int id;                 									//单词编号
    std::shared_ptr<PostingList>  postingList;   				        //指向包含该单词的倒排列表的指针
    unsigned long long docCount;               						    //出现过该单词的文档数
    unsigned long long totalCount;              					    //在所有文档中该单词出现的次数和
    InvertHashIndexType type;											//倒排序列的类型　０是通过ngram生成的word,1是通过分词算法生产的
    InvertedIndexHash(){
        docCount = 0;
        totalCount = 0;
    }
};
#endif
