#ifndef CONFIG_H
#define CONFIG_H

#include<iostream>
#include<fstream>
#include<string>
#include<map>

//mysql数据库相关配置
const std::string SQL_DB = "search";
const std::string SQL_URL = "tcp://127.0.0.1:3306";
const std::string SQL_USER = "root";
const std::string SQL_PWD = "1212";

//redis数据库相关配置
const std::string REDIS_HOST = "120.26.103.174";
const int REDIS_PORT = 6379;
const std::string REDIS_DB = "documentId";
const std::string REDIS_AUTH = "flare1111";

//mongodb相关配置
const std::string MONGO_HOST = "120.26.103.174";
const int MONGO_PORT = 27017;
const std::string MONGO_DB = "search";
const std::string MONGO_CONTAINER = "document";

enum InvertHashIndexType{
	ngramWord = 0,
	splitWord = 1
};

enum DOCUMENT_TYPE{
	html=1,
	pdf=2,
	word=3
};
#endif
