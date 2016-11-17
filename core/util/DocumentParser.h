#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include<iostream>
#include<string>
#include<map>
#include<vector>

#include"../model/InvertedIndexHash.h"
using namespace std;

/**
 * Document Parser,aid to parser document to invertedHashIndex
 * author jiangpengfei12@gmail.com
 * 2016-11-14
 */
class DocumentParser{
public:
	/**
	 * peel html page to document
	 * @param wstring html string
	 * @return main content of html page
	 */
	static wstring peel(wstring html);	
	
	/**
	 * parser text and get invertedHashIndex array
	 * @param document 
	 * @return invertedHashIndex array
	 */
	static vector<InvertedIndexHash> parser(wstring text);
	
	/**
	 * use n-gram to split word with into map<word,positions>
	 * @param text content
	 * @param step n
	 * @return map
	 */
	static map<wstring,vector<int> > ngram(wstring text,int step);
	
	/**
	 * use "word split" to split word with into map<word,positions>
	 * @param text content
	 * @return map
	 */
    static map<wstring,vector<int> > splitWord(wstring text);
};
#endif
