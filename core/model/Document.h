#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include<iostream>
#include<string>
#include"Constants.h"

using namespace std;

class Document{
    public:
        int id;                             //文档对应的数据库Id
        enum DOCUMENT_TYPE type;            //文档类型
        string title;                       //文档的标题
        string abstract;                    //文档摘要
        string url;                         //文档地址
        string author;                      //文档作者
        unsigned int wordNum;               //文档单词数
        string saveTime;                    //文档抓取日期
        string createTime;                  //文档创建日期    
        Document(string title,string abstract,string url,string author,unsigned int wordNum,string saveTime,string createTime);
        Document();
};

Document::Document(){

}

Document::Document(string title,string abstract,string url,string author,unsigned int wordNum,string saveTime,string createTime){
    this->title = title;
    this->abstract = abstract;
    this->url = url;
    this->author = author;
    this->wordNum = wordNum;
    this->saveTime = saveTime;
    this->createTime = createTime;    
}
#endif
