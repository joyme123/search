/**
 * filename:ConnectionPool.cpp
 * 数据库连接池实现类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include "ConnectionPool.h"

ConnectionPool* ConnectionPool::createConnectionPool(int maxConnCount){
    static ConnectionPool pool;
    pool.setMaxConnCount(maxConnCount);
    return &pool;
}

//构造函数
ConnectionPool::ConnectionPool(){
    
}

ConnectionPool::~ConnectionPool(){
    while(!this->connectionQueue.empty()){
        this->connectionQueue.front().close();  //关闭mysql连接
        this->connectionQueue.pop();            //出栈
    }
}

//从线程池中获取一个连接实例
Mysql ConnectionPool::getConnection(){
    m.lock();
    //连接池队列中还存在连接时，则直接返回
    if(!this->connectionQueue.empty()){
        Mysql conn = this->connectionQueue.front();
        this->connectionQueue.pop();        //出队列
        m.unlock();
        return conn;
    }

    //队列中的连接数是否超过最大值
    if(this->createCount >= this->maxConnCount){
        //超过
        sleep(3000);        //等待3秒
        if(this->createCount >= this->maxConnCount){
            throw TimeoutException();   
        }
    }
    Mysql* mysqlPtr = NULL;
    try{
        //没超过则继续创建
        Mysql mysql;
        this->createCount++;        //新创建的则在createCount自增1
        mysqlPtr = &mysql;
    }catch(sql::SQLException &e){
        LOG(ERROR) << "SimHashDAO->addSimHash(SimHash simHash):"<< e.getErrorCode()<<"--"<<e.what();
        m.unlock();
    }         
    m.unlock(); 
    return *mysqlPtr;
}

void ConnectionPool::retConnection(Mysql& connection){
    m.lock();
    connectionQueue.push(connection);
    m.unlock();
}