#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include<iostream>
#include<string>
#include<map>
#include<vector>

#include"config.h"
#include"util.h"
#include"../InvertedIndexHash.h"
#include"../../include/friso/friso_API.h"
#include"../../include/friso/friso.h"



/**
 * Document Parser,aid to parser document to invertedHashIndex
 * author jiangpengfei12@gmail.com
 * 2016-11-14
 */
class DocumentParser{
public:
	/**
	 * peel html page to document
	 * @param html string
	 * @return main content of html page
	 */
	static std::string peel(std::string html);	
	
	/**
	 * parser text and get invertedHashIndex array
	 * @param text parser text 
	 * @return invertedHashIndex array
	 */
	static std::vector<InvertedIndexHash> parser(std::string text);
	
	/**
	 * use n-gram to split word with into map<word,positions>
	 * @param text content
	 * @param step n
	 * @return map
	 */
	static std::map<std::string,std::vector<int> > ngram(std::string text,int step);
	
	/**
	 * use "word split" to split word with into map<word,positions>
	 * @param text content
	 * @return map
	 */
    static std::map<std::string,std::vector<int> > splitWord(std::string text,friso_mode_t mode);
    
    /**
     * input formated text and return a document object
     * @param formatText formated text like this:title|type|abstract|author|text|
     * @return document
     */
    static Document documentFormat(std::string formatText);
};
#endif
