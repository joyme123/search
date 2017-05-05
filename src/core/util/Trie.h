#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "src/core/model/Keyword.h"
/**
 * Trie树的实现，使用wstring来兼容汉字
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
        //递归删除所有结点
        void deleteAll(trie_node* node);

    public:
        /**
         * 搜索具有该前缀的所有词汇
         * @param prefix 前缀
         * @return std::vector<Keyword> 关键字数组
         */
        std::vector<Keyword> searchPrefix(std::wstring prefix);
        //析构Trie树
        ~Trie();
    protected:

};
#endif
