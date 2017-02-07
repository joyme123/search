/**
 * filename:SimHash.cpp
 * SimHash类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"SimHash.h"

SimHash::SimHash(){
}

std::vector<int> SimHash::getDocIds(){
    std::vector<int> ids;
    std::string tmpId;
    for(auto it = this->docIds.begin(); it != this->docIds.end(); it++){
        if(*it != '|'){
            tmpId.push_back(*it);
        }else{
            ids.push_back(std::stoi(tmpId));
        }
    }
    return ids;
}