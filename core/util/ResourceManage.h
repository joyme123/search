/**
 * 资源管理类，负责从redis队列中取出下一个要处理的文档id，然后根据文档id从Mongodb中查询出文档
 * author:jiang
 * date:2017-03-27
 */
#include <iostream>
#include <string>
#include <cpp_redis/cpp_redis>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


 class ResourceManage{
    private:
        //私有的初始化，防止对象的重复创建
        ResourceManage();
    public:
        /**
         * 获取资源管理的单例
         */
        ResourceManage getInstance(std::string redisHost,unsigned int redisPort,std::string mongoHost,unsigned int mongoPort);
        /**
         * 从redis中获取下一个文档的id
         * @return string 文档id
         */
        std::string getNext();

        /**
         * 从mongodb中根据文档id获取文档
         * @param id 文档id
         * @return string 文档
         */
        std::string getDocument(std::string id);
 };