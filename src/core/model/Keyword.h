/**
 * 查询关键字的提示
 * author:jiangpengfei
 * date:2017-05-05
 */
#ifndef KEYWORD_H
#define KEYWORD_H

#include <iostream>
#include <string>

 class Keyword{
    public:
        std::wstring word;
        unsigned int count;
        Keyword(std::wstring word,unsigned int count);
    private:
 };

 #endif