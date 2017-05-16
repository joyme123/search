/**
 * filename:PostingList.h
 * 倒排列表的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef POSTINGLIST_H
#define POSTINGLIST_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "src/core/model/Document.h"
#include "src/core/model/Word.h"
#include "src/core/util/util.h"

/**
 * (documentId,frequency)<pos1,pos2>
 */
class PostingList{
    public:
        unsigned int documentId;          											    //文档
        std::vector<int> positions;      												//该单词在文档中出现的位置信息
        std::shared_ptr<PostingList> next;            							        //指向下一个PostingList的指针
        PostingList();                                  								//default construct
        void generate(std::string postingListStr);       				 	            //construct
        
        //转换成id数组
        std::vector<unsigned int> toVector();            
};

#endif  
