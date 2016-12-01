#ifndef  DOCUMENT_H
#define DOCUMENT_H

#include<iostream>
#include<string>
#include"util/config.h"

class Document{
    public:
        unsigned int id;                             //文档对应的数据库Id
        enum DOCUMENT_TYPE type;            //文档类型
        std::string title;                       //文档的标题
        std::string abstract;                    //文档摘要
        std::string url;                         //文档地址
        std::string author;                      //文档作者
        std::string text;							//文档内容
        unsigned int wordNum;               //文档单词数
        std::string updateTime;                    //文档抓取日期
        std::string createTime;                  //文档创建日期    
        Document();
        Document(std::string title,std::string abstract,std::string url,std::string author,std::string text,unsigned int wordNum,std::string createTime,std::string updateTime);
        static DOCUMENT_TYPE getDocType(int type);
};

#endif
