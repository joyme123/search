#include "ConnectionPool.h"

ConnectionPool* ConnectionPool::createConnectionPool(int maxConnCount){
    static ConnectionPool pool;
    pool.setMaxConnCount(maxConnCount);
    return &pool;
}

//构造函数
ConnectionPool::ConnectionPool(){
    
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

    Mysql* mysqlPtr;
    try{
        //没超过则继续创建
        mysqlPtr = new Mysql;
        this->createCount++;        //新创建的则在createCount自增1
        
    }catch(sql::SQLException &e){
        LOG(ERROR) << "SimHashDAO->addSimHash(SimHash simHash):"<< e.getErrorCode()<<"--"<<e.what();
        m.unlock();
    }         
    m.unlock();
    return *mysqlPtr;          
}

void ConnectionPool::retConnection(Mysql connection){
    m.lock();
    connectionQueue.push(connection);
    m.unlock();
}