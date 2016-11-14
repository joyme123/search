#ifndef WORD_H
#define WORD_H
#include<iostream>
#include<string>

using namespace std;

class Word{
    public:
        int id;                 //单词对应的数据库Id
        string text;            //word的内容
        Word(string text);
        Word();

};

Word::Word(){
        
    }

Word::Word(string text){
    this->text = text;
}

#endif
