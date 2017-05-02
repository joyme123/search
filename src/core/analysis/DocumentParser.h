/**
 * Document Parser,封装了关于Document的解析函数
 * author jiangpengfei12@gmail.com
 * 2016-11-14
 */
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstddef>

#include "src/core/util/config.h"
#include "src/core/util/util.h"
#include "src/core/model/Package.h"
#include "src/core/model/InvertedIndexHash.h"
#include "src/include/json.hpp"

class DocumentParser{
private:
	/**
	 * HTML文档分析函数
	 * @param document对象引用,分析的结果存储在这个对象
	 * @param content 待分析的文本
	 * @return true分析成功，false分析失败
	 */
	static bool htmlFileAnalysis(Document &document,std::string& content);

	/**
	 * PDF文档分析函数
	 * @param document对象引用，分析的结果存储在这个对象
	 * @param content 待分析的文本
	 * @return true分析成功，false分析失败
	 */
	static bool pdfFileAnalysis(Document &document,std::string& content);

	/**
	 * WORD文档分析函数
	 * @param document对象引用，分析的结果存储在这个对象
	 * @param content 待分析的文本
	 * @return true分析成功，false分析失败
	 */
	static bool wordFileAnalysis(Document &document,std::string& content);
public:
	/**
	 * peel html page to document
	 * @param html string
	 * @return main content of html page
	 */
	static std::string peel(std::string& html);	
	
	/**
	 * parser text and get invertedHashIndex array
	 * @param text parser text 
	 * @return invertedHashIndex array
	 */
	static std::vector<InvertedIndexHash> parser(std::string& text);
    
    /**
     * input formated text and return a document object
     * @param formatText formated text like this:title|type|abstract|author|text|
     * @return document
     */
    static Document documentFormat(std::string& formatText);

	/**
	 * parse Package to Document
	 * @param package the package need to parse
	 * @return document 
	 */ 
	static Document documentFormat(Package& package);

	/**
	 * parse json to Document
	 * @param documentJson 需要解析的json
	 * @return document 
	 */ 
	static Document documentJsonFormat(std::string& documentJson);


};
#endif