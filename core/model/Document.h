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
        wstring title;                       //文档的标题
        wstring abstract;                    //文档摘要
        wstring url;                         //文档地址
        wstring author;                      //文档作者
        unsigned int wordNum;               //文档单词数
        wstring saveTime;                    //文档抓取日期
        wstring createTime;                  //文档创建日期    
        Document(wstring title,wstring abstract,wstring url,wstring author,unsigned int wordNum,wstring saveTime,wstring createTime);
        Document();
};

Document::Document(){

}

Document::Document(wstring title,wstring abstract,wstring url,wstring author,unsigned int wordNum,wstring saveTime,wstring createTime){
    this->title = title;
    this->abstract = abstract;
    this->url = url;
    this->author = author;
    this->wordNum = wordNum;
    this->saveTime = saveTime;
    this->createTime = createTime;    
}
#endif
