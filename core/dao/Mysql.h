#ifndef MYSQL_H
#define MYSQL_H
#include<iostream>
#include<stdlib.h>
#include<memory>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <cppconn/metadata.h>
#include<cppconn/prepared_statement.h>
#include <cppconn/statement.h>   
#include<cppconn/sqlstring.h>
#include <cppconn/resultset.h>
#include<cppconn/resultset_metadata.h>

#include <mysql_driver.h>
#include<mysql_connection.h>

using namespace std;

class Mysql{
    private:
        string user;
        string pass;
        string database;
        string url;
        sql::Driver* driver;
        shared_ptr<sql::Connection> conn;
        void connect(){
            if(conn == NULL){
				shared_ptr<sql::Connection> temp(this->driver->connect(this->url,this->user,this->pass));
                this->conn = temp;
                shared_ptr<sql::Statement> stm(this->conn->createStatement()); 
                stm->execute("use "+database);
            }
        }
    public:
        
        Mysql(){
            //get the instance of driver int construct function
			user = "5019";
			pass = "5019";
			database = "empdb";
			url = "tcp://115.29.114.202:3306";
            this->driver = sql::mysql::get_driver_instance();
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
            shared_ptr<sql::PreparedStatement> pstm(this->conn->prepareStatement(sqlString));
            return pstm;
        }
        
        /**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param sql,query sql string 
         * @return ResultSet* the query ResultSet
         */
        std::shared_ptr<sql::ResultSet> query(string sql){
            return this->query(this->prepare(sql));
        }
        
        /**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param pstm ,PreparedStatement* 
         * @return ResultSet* the query ResultSet
         */
        shared_ptr<sql::ResultSet> query(std::shared_ptr<sql::PreparedStatement> pstm){
            if(conn == NULL){
                this->connect();
            }
            shared_ptr<sql::ResultSet> res(pstm->executeQuery());
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
