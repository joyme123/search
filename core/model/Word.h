#ifndef WORD_H
#define WORD_H
#include<iostream>
#include<string>

using namespace std;

class Word{
    public:
        int id;                 //单词对应的数据库Id
        wstring text;            //word的内容
        Word(wstring text);
        Word();

};

Word::Word(){
        
    }

Word::Word(wstring text){
    this->text = text;
}

#endif
