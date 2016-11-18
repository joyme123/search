#ifndef POSTINGLIST_H
#define POSTINGLIST_H
#include<iostream>
#include<string>
#include<vector>
#include<memory>

#include"Document.h"
#include"Word.h"
using namespace std;

class PostingList{
    public:
        Document document;          			//文档
        vector<int> positions;      				//该单词在文档中出现的位置信息
        shared_ptr<PostingList> next;          	//指向下一个PostingList的指针
};

#endif
