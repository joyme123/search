#ifndef SIMHASH_H
#define SIMHASH_H

#include<iostream>
#include<string>
#include<vector>
#include"util/util.h"

class SimHash{
    public:
        unsigned int id;
        std::string simHash;            //SimHash指纹
        std::string docIds;             //具有这个simHash的文档id,存储格式11|12|13|14|
        std::string createTime;         //创建时间
        std::string updateTime;         //更新时间
        SimHash();
        std::vector<int> getDocIds();
};

#endif