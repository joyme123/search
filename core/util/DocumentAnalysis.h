#ifndef DOCUMENTANALYSIS_H
#define DOCUMENTANALYSIS_H
#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include"util.h"

class DocumentAnalysis{
    private:
        int k;                     //行块的大小
        std::vector<char> blankChars;       //空白字符集合
        int threshold;             //骤起点的阈值
    public:

        DocumentAnalysis();

        /**
         * 提取网页正文函数，参考了《基于行块分布函数的通用网页正文抽取-陈 鑫 (Xin Chen)》
         * @param html 网页文本
         * @param 去除html标签的正则
         * @return 提取出来的网页正文
         */
        std::string htmlAnalysis(std::string html,std::regex e) const;

        /**
         * 重载函数，使用默认的html标签去除正则，提取网页正文函数，参考了《基于行块分布函数的通用网页正文抽取-陈 鑫 (Xin Chen)》
         * @param html 网页文本
         * @param 去除html标签的正则
         * @return 提取出来的网页正文
         */
        std::string htmlAnalysis(std::string html) const;

        void setBlockLines(const unsigned int k);

        void setThreshold(const unsigned int threshold);
};

#endif