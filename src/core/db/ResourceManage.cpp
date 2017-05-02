#include "ResourceManage.h"

ResourceManage::ResourceManage(std::string redisHost,unsigned int redisPort,
        std::string mongoHost,unsigned int mongoPort):mongoClient{mongocxx::uri{}}{

    this->redisClient.connect(redisHost, redisPort, [](cpp_redis::redis_client&) {
        std::cout << "client disconnected (disconnection handler)" << std::endl;
    });

    this->mongoCollection = this->mongoClient["search"]["document"];
}

ResourceManage* ResourceManage::getInstance(std::string redisHost,unsigned int redisPort,std::string mongoHost,unsigned int mongoPort){
    static ResourceManage instance(redisHost,redisPort,mongoHost,mongoPort);
    return &instance;
}

std::string ResourceManage::getNextDocument(){
    std::string documentId;
    std::string documentJson;       //保存最后的结果
    this->redisClient.lpop("documentId",[&documentId](cpp_redis::reply& reply) {
        if (reply.is_string()){
            documentId = reply.as_string();
        }
    });
    this->redisClient.sync_commit();

    auto maybe_result = this->mongoCollection.find_one(bsoncxx::builder::stream::document{} << "_id" << documentId << bsoncxx::builder::stream::finalize);
    if(maybe_result) {
        documentJson = bsoncxx::to_json(*maybe_result);
    }    

    return documentJson;
}