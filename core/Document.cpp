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

DOCUMENT_TYPE Document::getDocType(int type){
	switch(type){
		case 1:
			return html;
		case 2:
			return pdf;
		case 3:
			return word;
	}
	return html;
}