#ifndef CONFIG_H
#define CONFIG_H

#include<iostream>
#include<ifstream>
#include<string>
#include<map>

#define FRISO_DICT_PATH "resource/friso.ini"
#define FREQUENCY_DICT_PATH "resource/frequency/cn.txt"

enum InvertHashIndexType{
	ngramWord = 0,
	splitWord = 1
};

enum DOCUMENT_TYPE{
	html=1,
	pdf=2,
	word=3
};

static std::map<std::string,double> frequency;			//该变量请不要直接使用
static bool frequencyInit = false;

static std::map<std::string,double>  initFrequencyDict();
}

#endif
