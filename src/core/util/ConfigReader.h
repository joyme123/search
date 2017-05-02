#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <glog/logging.h>

#ifndef CONFIGREADER_H
#define CONFIGREADER_H
class ConfigReader{
    public:
        static ConfigReader* getInstance();
        static ConfigReader* getInstance(const char* path);
        /**
         * 打开配置文件
         * @param path 配置文件路径
         */
        void open();

        /**
         * 获取某个配置
         * @param key 键
         * @return string 存在则返回值，不存在则返回""
         */
        std::string get(const std::string key);
    protected:


    private:
        /**
         * 私有的构造方法,防止被直接用来实例化对象
         *
         */
        ConfigReader(const char* tmpPath){
            this->path = tmpPath;
            this->open();
        }
        ConfigReader& operator=(const ConfigReader&);  //禁用复制
        std::map<std::string,std::string> config;
        const char* path;
};
#endif