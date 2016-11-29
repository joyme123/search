#ifndef POSTINGLIST_H
#define POSTINGLIST_H
#include<iostream>
#include<string>
#include<vector>
#include<memory>

#include"Document.h"
#include"Word.h"
#include"util/util.h"

/**
 * (documentId;frequency;<pos1;pos2>)
 */
class PostingList{
    public:
        unsigned int documentId;          											//文档
        std::vector<int> positions;      												//该单词在文档中出现的位置信息
        std::shared_ptr<PostingList> next;            							//指向下一个PostingList的指针
        PostingList();                                  										//default construct
        void generate(std::string postingListStr);       				 	//construct
};

#endif  
