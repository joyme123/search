#ifndef WORDSPLITSINGLETON_H
#define WORDSPLITSINGLETON_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "src/core/util/ConfigReader.h"
#include "src/include/friso/friso_API.h"
#include "src/include/friso/friso.h"

class WordSplitSingleton{
    private:
        friso_t friso;
        friso_config_t config;
        WordSplitSingleton(friso_mode_t mode);
    public:

        static WordSplitSingleton* getInstance(friso_mode_t mode);
        ~WordSplitSingleton();  //析构
        /**
        * 使用ngram算法进行文本的分词
        * @param text 文本内容
        * @param step 分词步长
        * @return map key为单词，value保存单词出现的位置
        */
        std::map<std::string,std::vector<int> > ngram(std::string& text,int step);

        /**
        * 基于friso的分词函数
        * @param text 文本内容
        * @param mode friso支持的分词模式
        * @return map key为单词，value保存单词出现的位置
        */
        std::map<std::string,std::vector<int> > splitWord(std::string& text);

};

#endif