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


class Mysql{
    private:
        std::string user;
        std::string pass;
        std::tring database;
        std::string url;
        std::sql::Driver* driver;
        std::shared_ptr<sql::Connection> conn;
        void connect();
    public:
        
        Mysql();
        
        std::shared_ptr<sql::Connection> getConnection();
        
        /**
         * prepare a str
         * @param string the sql string
         * @return PreparedStatement* pstm
         */
        std::shared_ptr<std::sql::PreparedStatement> prepare(std::string str);
        
        /**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param sql,query sql string 
         * @return ResultSet* the query ResultSet
         */
        std::shared_ptr<std::sql::ResultSet> query(std::string sql);
        
		/**
         * query a sql prepared_statement,remember to delete the ResultSet when don't need it
         * @param pstm ,PreparedStatement* 
         * @return ResultSet* the query ResultSet
         */
        std::shared_ptr<std::sql::ResultSet> query(std::shared_ptr<sql::PreparedStatement> pstm);
        
        /**
         * execute a insert sql
         * @param sql ,insert sql string
         * @return insert record id
         */
        int insert(std::string sql);
        
        /**
         * execute a insert sql
         * @param pstm ,PreparedStatement
         * @return insert record id
         */
        int insert(std::shared_ptr<sql::PreparedStatement> pstm);
        
        /**
         * execute a update sql
         * @param sql ,update sql string
         * @return affect rows
         */
        int update(std::string sql);
        
        /**
         * execute a update PreparedStatement
         * @param pstm ,update PreparedStatement
         * @return affect rows
         */
        int update(std::shared_ptr<sql::PreparedStatement> pstm);
        
        /**
         * execute a delete PreparedStatement
         * @param sql ,delete string
         * @return affect rows
         */
        int del(std::string sql);
        
        /**
         * execute a delete PreparedStatement
         * @param pstm ,PreparedStatement* pstm
         * @return affect rows
         */
        int del(std::shared_ptr<sql::PreparedStatement> pstm);


};

#endif