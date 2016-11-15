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
	 * @param string html string
	 * @return main content of html page
	 */
	static string peel(string html);	
	
	/**
	 * parser text and get invertedHashIndex array
	 * @param document 
	 * @return invertedHashIndex array
	 */
	static vector<InvertedIndexHash> parser(string text);
	
	/**
	 * use n-gram to split word with into map<word,positions>
	 * @param text content
	 * @param step n
	 * @return map
	 */
	static map<string,vector<int> > ngram(string text,int step);
	
	/**
	 * use "word split" to split word with into map<word,positions>
	 * @param text content
	 * @return map
	 */
    static map<string,vector<int> > splitWord(string text);
};
#endif
