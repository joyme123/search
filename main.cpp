#include <iostream>
#include<string>
#include "core/DocumentDAO.h"
#include "core/WordDAO.h"
#include "core/Document.h"
#include "core/util/DocumentParser.h"

int main(int argc, char **argv) {
	//title|type|author|url|text
	wstring documentFormat = L"Java虚拟机学习记录(九)——类文件结构(上)|1|joyme|http://myway5.com/?post=54|在Java开发中，可以通过javac将.java的源代码编译为.class的类文件。之前一直以为，只有java语言可以编译为.class。但是在前些天的学习中，了解到不仅仅是Java语言可以编译成.class文件然后运行在Java虚拟机上，Clojure、Groovy、JRuby、Jython、Scala等语言都可以运行在Java虚拟机上。觉得这真是太神奇了。今天这一章的内容刚好可以解释这些";
	Document document = DocumentParser::documentFormat(documentFormat);
	DocumentDAO doc;
    int id = doc.addDocument(document);
	document.id = id;
	std::map<wstring,vector<int> > map = DocumentParser::splitWord(document.text,__FRISO_COMPLEX_MODE__);
	for(std::map<wstring,vector<int> >::iterator it = map.begin(); it != map.end(); it++){
		std::wcout << it->first << " ";
		std::vector<int> v = it->second;
		for(std::vector<int>::iterator vit = v.begin(); vit != v.end(); vit++){
			std::wcout << *vit << ",";
		}
		std::wcout << endl;
	}
	std::cout << id << endl;
    return 0;
}
