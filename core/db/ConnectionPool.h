/**
 * filename:ConnectionPool.h
 * 数据库连接池类头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <iostream>
#include <queue>
#include <mutex>
#include <glog/logging.h>
#include "Mysql.h"
#include "core/exception/TimeoutException.h"
/**
 * 线程池类
 * author:jiangpengfei12@gmail.com
 * date:2016-12-23
 */
class ConnectionPool{
    private:
        std::queue<Mysql> connectionQueue;              //连接队列
        int createCount;                                //已创建的连接数
        int maxConnCount;                               //最大连接数
        ConnectionPool();                               //私有的构造函数                              
        std::mutex m;
    public:
        ~ConnectionPool();                              //析构函数

        /**
         * 创建线程池,单例模式,这是线程安全的
         * @param maxConnCount 最大连接数
         */
        static ConnectionPool* createConnectionPool(int maxConnCount);       

        /**
         * 获取一个连接实例,线程安全,当连接数达到最大并且当前没有空闲的连接时，等待3秒后会抛出超时异常
         */
        Mysql getConnection();  

        /**
         * 将连接放回连接池
         * @param connection
         */

         void retConnection(Mysql& connection);

        /**
         * 获取最大连接数
         * @return int 最大连接数
         */          
         int getMaxConnCount(){
             return ConnectionPool::maxConnCount;
         }       

         /**
          * 设置最大连接数
          * @param count 最大连接数
          */
          void setMaxConnCount(int count){
            ConnectionPool::maxConnCount = count;
          }     

};


#endif