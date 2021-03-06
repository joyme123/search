#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "src/core/model/Keyword.h"
#include "src/core/util/util.h"
/**
 * Trie树的实现，使用wstring来兼容汉字
 * 实现了持久化以及从持久化文件中恢复
 * TODO:定时持久化和增量持久化策略
 * @author jiangpengfei
 * @date   2017-05-05
 */
class Trie{
    private:
        struct trie_node{
            bool isKey;         //是否是关键字
            unsigned int count; //该点统计的词的数量
            std::map<wchar_t,trie_node*> children;

            trie_node():isKey(false),count(0){

            }
        } node;
        
        /**
         * DFS找到所有前缀是word的词语
         * @param word 前缀单词
         * @param tmpNode 当前处于的结点
         * @param words 存储结果词语
         */
        void dfs(std::wstring word,trie_node* tmpNode,std::vector<Keyword>& words);

        void persistDfs(std::wstring word,trie_node* tmpNode,std::ofstream& ofstream);

        //递归删除所有结点
        void deleteAll(trie_node* node);

    public:
        /**
         * 搜索具有该前缀的所有词汇
         * @param prefix 前缀
         * @param num    需要的前几个词汇,-1代表显示所有结果
         * @return std::vector<Keyword> 关键字数组
         */
        std::vector<Keyword> searchPrefix(std::wstring prefix,int num = -1);

        /**
         * 将搜索词 加入到Trie树中
         * @param word 搜索词
         * @param n    该搜索词添加的搜索数量
         * @return bool 加入成功或失败
         */
        bool addWordToTrie(std::wstring word,const unsigned int n = 1);

        /**
         * 持久化
         * @param path 输出路径
         */
        void persist(std::string& path);

        /**
         * 从输入流中恢复Trie
         * @param ifstream 输入路径
         *
         */
        void read(std::string& path);
        
        //析构Trie树
        ~Trie();
    protected:

};
#endif
