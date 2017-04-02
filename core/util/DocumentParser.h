/**
 * Document Parser,封装了关于Document的解析函数
 * author jiangpengfei12@gmail.com
 * 2016-11-14
 */
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<cstddef>

#include"config.h"
#include"util.h"
#include "../Package.h"
#include"../InvertedIndexHash.h"
#include"../../include/friso/friso_API.h"
#include"../../include/friso/friso.h"
#include"../../include/json.hpp"

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
	 * 使用ngram算法进行文本的分词
	 * @param text 文本内容
	 * @param step 分词步长
	 * @return map key为单词，value保存单词出现的位置
	 */
	static std::map<std::string,std::vector<int> > ngram(std::string& text,int step);
	
	/**
	 * 基于friso的分词函数
	 * @param text 文本内容
	 * @param mode friso支持的分词模式
	 * @return map key为单词，value保存单词出现的位置
	 */
    static std::map<std::string,std::vector<int> > splitWord(std::string& text,friso_mode_t mode);
    
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
