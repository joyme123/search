#include "ResourceManage.h"

ResourceManage::ResourceManage(){
    ConfigReader* reader = ConfigReader::getInstance();
    this->redisHost = reader->get("redis_host");
    this->redisPort = stoi(reader->get("redis_port"));
    this->redisDb = reader->get("redis_db");
    this->mongoHost = reader->get("mongo_host");
    this->mongoPort = reader->get("mongo_port");
    this->redisAuth = reader->get("redis_auth");
    this->mongoDb = reader->get("mongo_db");
    this->mongoContainer = reader->get("mongo_container");


    //redis的连接
    this->redisClient.connect(redisHost, redisPort, [](cpp_redis::redis_client&) {
        std::cout << "client disconnected (disconnection handler)" << std::endl;
    });

    if(this->redisAuth != ""){
        this->redisClient.auth(this->redisAuth,[](cpp_redis::reply& reply) {
            if (reply.is_string()){
                std::cout << reply.as_string() << std::endl;
            }else{
                std::cout << "reply格式是啥" << std::endl;
            }
        });
    }

    //mongodb的连接
    mongocxx::uri uri("mongodb://"+this->mongoHost+":"+this->mongoPort);
    this->mongoClient = mongocxx::client(uri);
    this->mongoCollection = this->mongoClient[this->mongoDb][this->mongoContainer];
}

ResourceManage* ResourceManage::getInstance(){
    static ResourceManage instance;
    return &instance;
}

std::string ResourceManage::getNextDocument(){
    std::string documentId;
    std::string documentJson;       //保存最后的结果
    this->redisClient.lpop(this->redisDb,[&documentId](cpp_redis::reply& reply) {
        if (reply.is_string()){
            documentId = reply.as_string();
        }else{
            //std::cout << "redis中已经不存在待处理的文档id" << std::endl;
            documentId = "";
        }
    });
    this->redisClient.sync_commit();
    if(documentId != ""){
        bsoncxx::oid myoid(documentId);
        auto maybe_result = this->mongoCollection.find_one(bsoncxx::builder::stream::document{} << "_id" << myoid << bsoncxx::builder::stream::finalize);
        if(maybe_result) {
            documentJson = bsoncxx::to_json(*maybe_result);
        }    
    }else{
        documentJson = "";
    }
    return documentJson;
}