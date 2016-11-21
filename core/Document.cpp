#include"Document.h"
Document::Document()
{
}

Document::Document(std::wstring title,std::wstring abstract,std::wstring url,std::wstring author,std::wstring text,unsigned int wordNum,std::wstring createTime,std::wstring updateTime){
    this->title = title;
    this->abstract = abstract;
    this->url = url;
    this->author = author;
	this->text = text;
    this->wordNum = wordNum;
    this->createTime = createTime;    
	this->updateTime = updateTime;
}
