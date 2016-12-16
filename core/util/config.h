#ifndef CONFIG_H
#define CONFIG_H

#include<iostream>
#include<fstream>
#include<string>
#include<map>

#ifndef RESOURCE_PATH
#define RESOURCE_PATH

#define FRISO_DICT_PATH "resource/friso.ini"
#define FREQUENCY_DICT_PATH "resource/frequency/cn.txt"
#define STOPWORD_DICT_PATH "resource/stopword/word.txt"

#endif
enum InvertHashIndexType{
	ngramWord = 0,
	splitWord = 1
};

enum DOCUMENT_TYPE{
	html=1,
	pdf=2,
	word=3
};

/**
 * 初始化词频表
 * @return 词频结果
 */
std::map<std::string,double>  initFrequencyDict();

/**
 * 初始化stopword词汇表
 * @return stopWord词汇表
 */

std::map<std::string,int> initStopWordDict();

#endif
