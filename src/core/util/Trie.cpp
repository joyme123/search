#include "src/core/util/Trie.h"

void Trie::dfs(std::wstring word,trie_node* tmpNode,std::vector<Keyword>& words){
     if(tmpNode->isKey){
        //如果当前节点是关键字
        words.push_back(Keyword(word,tmpNode->count));
    }
    if(tmpNode->children.size() > 0){
        //当还有下一层
        for(auto it = tmpNode->children.begin(); it != tmpNode->children.end(); it++){
            dfs(word+(it->first),it->second,words);    
        }
    }
}

std::vector<Keyword> Trie::searchPrefix(std::wstring prefix,int num){
    std::vector<Keyword> words;
    if(prefix.size() == 0){
        return words;
    }

    trie_node* tmp = &(this->node);

    for(int i = 0; i < prefix.length(); i++){
        if(tmp->children.find(prefix[i]) != tmp->children.end()){
            //当前节点有指向到prefix的字符记录

            //指针移到下一个节点
            tmp = tmp->children.find(prefix[i])->second; 
        }else{
            return words;
        }
    }
    trie_node* tmpRef = tmp;
    
    this->dfs(prefix,tmpRef,words);

    std::sort(words.begin(),words.end(),[](Keyword &l,Keyword &r){
        return l.count > r.count;
    });

    if(num != -1){
        if(words.size() > num){
            Keyword tmpK(L"",0);
            words.resize(num,tmpK);      //只保留需要的前几个数据
        }
    }
    return words;
}


bool Trie::addWordToTrie(std::wstring word){

    trie_node* tmp = &(this->node);

    for(int i = 0; i < word.length(); i++){
        if(tmp->children.find(word[i]) == tmp->children.end()){
            //当前节点没有指向到word的当前字符的记录
            //创建一个新的trie_node
            trie_node* nextNode = new trie_node;
            std::pair<wchar_t,trie_node*> k(word[i],nextNode);
            //将当前字符指向下一个节点
            tmp->children.insert(k);
            //指针移到下一个节点
            tmp = nextNode;
        }else{
            tmp = tmp->children.find(word[i])->second; 
        }
    }
    tmp->isKey = true;
    tmp->count++;      //计数器加一
    return true;
}

void Trie::deleteAll(trie_node* node){
    if(node->children.size() > 0){
        //当还有下一层
        for(auto it = node->children.begin(); it != node->children.end(); it++){
            deleteAll(it->second);    
        }
    }
    if(node != &(this->node)){
        //std::cout << "delete" << std::endl;
        delete node;
    }
}

// void Trie::persist(std::wstring word,trie_node* tmpNode,std::ofstream ofstream){
//     if(tmpNode->isKey){
//         //如果当前节点是关键字
//         ofstream << word << std::endl;
//     }

//     if(tmpNode->children.size() > 0){
//         //当还有下一层
//         for(auto it = tmpNode->children.begin(); it != tmpNode->children.end(); it++){
//             persist(word+(it->first),it->second,ofstream);    
//         }
//     }
// }


Trie::~Trie(){
    //析构的时候先执行一次持久化
    //TODO

    this->deleteAll(&(this->node));
    //std::cout << "Trie树析构完成" << std::endl;
}