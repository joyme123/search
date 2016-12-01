#include"Document.h"
Document::Document()
{
}

Document::Document(std::string title,std::string abstract,std::string url,std::string author,std::string text,unsigned int wordNum,std::string createTime,std::string updateTime){
    this->title = title;
    this->abstract = abstract;
    this->url = url;
    this->author = author;
	this->text = text;
    this->wordNum = wordNum;
    this->createTime = createTime;    
	this->updateTime = updateTime;
}
