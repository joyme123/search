#ifndef MYSQL_H
#define MYSQL_H
#include<iostream>
#include<stdlib.h>
#include<tr1/memory>

#include <mysql_driver.h>
#include<cppconn/prepared_statement.h>
#include<cppconn/sqlstring.h>
#include <cppconn/connection.h>

using namespace std;

class Mysql{
    private:
        const string user = "root";
        const string pass = "jpf19950206";
        const string database = "test";
        const string url = "tcp://localhost:3306";
                
        void connect(){
            if(conn == NULL){
                this->conn =  make_shared<sql::Connection>(this->driver->connect(this->url,this->user,this->pass));
            }
        }
    public:
        std::tr1::shared_ptr<sql::mysql::MySQL_Driver> driver;
        std::tr1::shared_ptr<sql::Connection> conn;
        
        Mysql(){
            //get the instance of driver int construct function
            this->driver = make_shared<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
        }
        
        shared_ptr<sql::Connection> getConnection(){
            if(conn == NULL){
                this->connect();
            }
            return this->conn;
        }
        
        /**
         * prepare a str
         * @param string the sql string
         * @return PreparedStatement* pstm
         */
        shared_ptr<sql::PreparedStatement> prepare(string str){
            if(conn == NULL){
                this->connect();
            }
            sql::SQLString sqlString(str); 
            std::tr1::shared_ptr<sql::PreparedStatement> pstm = make_shared<sql::PreparedStatement>(this->conn->prepareStatement(sqlString));
            return pstm;
        }
        
        /**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param sql,query sql string 
         * @return ResultSet* the query ResultSet
         */
        std::tr1::shared_ptr<sql::ResultSet> query(string sql){
            return this->query(this->prepare(sql));
        }
        
        /**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param pstm ,PreparedStatement* 
         * @return ResultSet* the query ResultSet
         */
        std::tr1::shared_ptr<sql::ResultSet> query(shared_ptr<sql::PreparedStatement> pstm){
            if(conn == NULL){
                this->connect();
            }
            std::tr1::shared_ptr<sql::ResultSet> res = make_shared<sql::ResultSet>(pstm->executeQuery());
            return res;    
        }
        
        /**
         * execute a insert sql
         * @param sql ,insert sql string
         * @return affect rows
         */
        int insert(string sql){
            return this->insert(this->prepare(sql));
        }
        
        /**
         * execute a insert sql
         * @param pstm ,PreparedStatement
         * @return affect rows
         */
        int insert(shared_ptr<sql::PreparedStatement> pstm){
            if(conn == NULL){
                this->connect();
            }
            int affectCols = pstm->executeUpdate();
            pstm->getUpdateCount();
            return affectCols;
        }
        
        /**
         * execute a update sql
         * @param sql ,update sql string
         * @return affect rows
         */
        int update(string sql){
            return this->update(this->prepare(sql));
        }
        
        /**
         * execute a update PreparedStatement
         * @param pstm ,update PreparedStatement
         * @return affect rows
         */
        int update(shared_ptr<sql::PreparedStatement> pstm){
            if(conn == NULL)
                this->connect();
            int affectCols = pstm->executeUpdate();
            return affectCols;
        }
        
        /**
         * execute a delete PreparedStatement
         * @param sql ,delete string
         * @return affect rows
         */
        int del(string sql){
            return this->del(this->prepare(sql));
        }
        
        /**
         * execute a delete PreparedStatement
         * @param pstm ,PreparedStatement* pstm
         * @return affect rows
         */
        int del(shared_ptr<sql::PreparedStatement> pstm){
            if(conn == NULL)
                this->connect();
            int affectCols = pstm->executeUpdate();
            return affectCols;
        }


};

#endif
