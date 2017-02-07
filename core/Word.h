/**
 * filename:Word.h
 * 单词类的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef WORD_H
#define WORD_H
#include<iostream>
#include<string>

class Word{
    public:
        int id;                 //单词对应的数据库Id
        std::string text;            //word的内容
        Word(std::string text);
        Word();

};

#endif
