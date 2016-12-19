#include<iostream>
#include<string>

class SimHash{
    public:
        int id;
        std::string simHash;            //SimHash指纹
        std::string docIds;             //具有这个simHash的文档id
        std::string createTime;         //创建时间
        std::string updateTime;         //更新时间
};