#ifndef WORD_H
#define WORD_H
#include<iostream>
#include<string>

class Word{
    public:
        int id;                 //单词对应的数据库Id
        std::wstring text;            //word的内容
        Word(std::wstring text);
        Word();

};

#endif
