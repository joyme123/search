/**
 * 资源管理类，负责从redis队列中取出下一个要处理的文档id，然后根据文档id从Mongodb中查询出文档
 * author:jiang
 * date:2017-03-27
 */
#ifndef RESOURCEMANAGE_H
#define RESOURCEMANAGE_H

#include <iostream>
#include <string>
#include <cpp_redis/cpp_redis>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/v_noabi/bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>


 class ResourceManage{
    private: 
        mongocxx::client mongoClient;
        cpp_redis::redis_client redisClient;
        mongocxx::collection  mongoCollection;
        //私有的初始化，防止对象的重复创建
        ResourceManage(std::string redisHost,unsigned int redisPort,
        std::string mongoHost,unsigned int mongoPort);
    public:
        /**
         * 获取资源管理的单例
         */
        static ResourceManage* getInstance(std::string redisHost,unsigned int redisPort,std::string mongoHost,unsigned int mongoPort);

        /**
         * 从mongodb中根据文档id获取文档
         * @param id 文档id
         * @return string 文档
         */
        std::string getNextDocument();
 };

 #endif