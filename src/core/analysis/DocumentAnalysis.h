/**
 * 文档分析类
 * 1.正文提取，推荐使用improvedHtmlAnalysis()
 * author:jiangpengfei12@gmail.com
 * date:  2016-12-12
 */
#ifndef DOCUMENTANALYSIS_H
#define DOCUMENTANALYSIS_H
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "src/core/util/util.h"

class DocumentAnalysis{
    private:
        int k;                              //行块的大小
        std::vector<char> blankChars;       //空白字符集合
        int threshold;                      //骤起点的阈值
    public:

        DocumentAnalysis();

        /**
         * 利用正则表达式去除网页标签
         * @param html 引用传参,要处理的Html页面
         * @return 引用返回值,处理好的html页面
         */
         std::string htmlPeel(std::string& html) const;

        //  /**
        //   * 利用正则表达式去除网页标签
        //   * @param html 引用传参,要处理的Html页面
        //   * @param regex 自定义正则
        //   * @return 引用返回值,处理好的html页面
        //   */
        //  std::string htmlPeel(std::string& html,std::regex regex) const;

        /**
         * 去除<p>、<img>、<hx>等单独占用的行,将单个空<div></div>块的权重占行权重降为1，时间复杂度O(n)
         * @param html 要处理的网页字符串
         * @return 处理好的网页内容
         */
         std::string htmlFormat(std::string& html) const;


        /**
         * 基于行块提取网页正文函数，参考了《基于行块分布函数的通用网页正文抽取-陈 鑫 (Xin Chen)》,
         * 优点:对于文本内容较多，文章内html标签少的网页正文的网页提取效果很好，并且可以做到O(n)的时间复杂度,正则匹配复杂度为O(n),替换为O(n),页面的分析为O(n)
         * 缺点:对于正文部分图片多，使用MarkDown等富文本编辑器时，提取效果较差，很难完全提取,可以通过调整k和threshold的值提高精确度
         * @param peeledHtml 被去除网页标签的网页文本
         * @return 提取出来的网页正文
         */
        std::string fastHtmlAnalysis(std::string& peeledHtml) const;


        /**
         * 在fastHtmlAnalysis基础上的一次改进，针对使用MarkDown等富文本编辑器和图片较多的网页，去除<p>、<img>、<hx>等单独占用的行,将单个空<div></div>块的权重占行权重降为1,删除处理时间复杂度为O(n),所以整体的时间复杂度不变，仍然为O(n)
         * @param html 网页文本
         * @return 提起出来的网页文本
         */
        std::string improvedHtmlAnalysis(std::string& html) const;

        /**
         * 设置一个行块最多容纳几行
         * @param k 行数
         */
        void setBlockLines(const int k);

        /**
         * 设置阈值
         * @param threshold 要设置的阈值
         */
        void setThreshold(const int threshold);
};

#endif