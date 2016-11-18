#include"Document.h"

Document::Document(wstring title,wstring abstract,wstring url,wstring author,wstring text,unsigned int wordNum,wstring saveTime,wstring createTime){
    this->title = title;
    this->abstract = abstract;
    this->url = url;
    this->author = author;
	this->text = text;
    this->wordNum = wordNum;
    this->saveTime = saveTime;
    this->createTime = createTime;    
}