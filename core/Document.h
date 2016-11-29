#ifndef  DOCUMENT_H
#define DOCUMENT_H

#include<iostream>
#include<string>
#include"util/config.h"

class Document{
    public:
        unsigned int id;                             //文档对应的数据库Id
        enum DOCUMENT_TYPE type;            //文档类型
        std::wstring title;                       //文档的标题
        std::wstring abstract;                    //文档摘要
        std::wstring url;                         //文档地址
        std::wstring author;                      //文档作者
        std::wstring text;							//文档内容
        unsigned int wordNum;               //文档单词数
        std::wstring updateTime;                    //文档抓取日期
        std::wstring createTime;                  //文档创建日期    
        Document();
        Document(std::wstring title,std::wstring abstract,std::wstring url,std::wstring author,std::wstring text,unsigned int wordNum,std::wstring createTime,std::wstring updateTime);
};

#endif
