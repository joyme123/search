#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include<iostream>
#include<string>
#include<map>
#include<vector>

#include"util.h"
#include"../model/InvertedIndexHash.h"
#include"../../include/friso/friso_API.h"
#include"../../include/friso/friso.h"
using namespace std;

#define FRISO_DICT_PATH "../../resource/friso.ini"

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
	static wstring peel(wstring html);	
	
	/**
	 * parser text and get invertedHashIndex array
	 * @param text parser text 
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
    static map<wstring,vector<int> > splitWord(wstring text,friso_mode_t mode);
};
#endif
