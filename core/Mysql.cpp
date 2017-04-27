/**
 * filename:Mysql.cpp
 * Mysql数据库类，封装了基本的增删改查以及事务管理
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"Mysql.h"

void Mysql::connect(){
	if(this->conn == NULL){
		this->conn = this->driver->connect(this->url,this->user,this->pass);
		std::shared_ptr<sql::Statement> stm(this->conn->createStatement()); 
		stm->execute("use "+this->database);
	}
}
Mysql::Mysql(){
	//get the instance of driver in construct function
	// this->user = "5019";
	// this->pass = "5019";
	// this->database = "empdb";
	// this->url = "tcp://115.29.114.202:3306";
	this->user = "root";
	this->pass = "1212";
	this->database = "search";
	this->url = "tcp://127.0.0.1:3306";
	this->driver = sql::mysql::get_driver_instance();
	this->conn = NULL;		//初始化为空
}

        
sql::Connection* Mysql:: getConnection(){
	this->connect();
	return this->conn;
}

void Mysql::close(){
	this->conn->close();	//关闭连接
	delete this->conn;		//销毁变量
}

void Mysql::beginTransaction(){
	if(this->conn == NULL){
		this->connect();
	}
	this->conn->setAutoCommit(false);      //open transaction
}

void Mysql::commit(){
	this->conn->commit();
    this->conn->setAutoCommit(true);
}


void Mysql::rollback(){
	this->conn->rollback();
    this->conn->setAutoCommit(true);      //end transaction
}
        

std::shared_ptr<sql::PreparedStatement> Mysql:: prepare(std::string str){
	if(this->conn == NULL){
		this->connect();
	}
	sql::SQLString sqlString(str); 
	std::shared_ptr<sql::PreparedStatement> pstm(this->conn->prepareStatement(sqlString));
	return pstm;
}

std::shared_ptr<sql::ResultSet> Mysql:: query(std::string sql){
	return this->query(this->prepare(sql));
}
        

std::shared_ptr<sql::ResultSet> Mysql:: query(std::shared_ptr<sql::PreparedStatement> pstm){
	if(this->conn == NULL){
		this->connect();
	}
	std::shared_ptr<sql::ResultSet> res(pstm->executeQuery());
	return res;    
}

int Mysql:: insert(std::string sql){
	return this->insert(this->prepare(sql));
}
        

int Mysql:: insert(std::shared_ptr<sql::PreparedStatement> pstm){
	if(this->conn == NULL){
		this->connect();
	}
	pstm->execute();

	sql::Statement *stmt;
	stmt = this->conn->createStatement();
	//last_insert_id(在多个数据库连接下安全)
	sql::ResultSet*  res = stmt->executeQuery("select last_insert_id()");
	int id = -1;
	if(res->next())
		id = res->getInt(1);
	
	delete stmt;
	delete res;		//删除res指针指向的内存
	return id;
}
        

int Mysql::update(std::string sql){
	return this->update(this->prepare(sql));
}

int Mysql::update(std::shared_ptr<sql::PreparedStatement> pstm){
	if(this->conn == NULL){
		this->connect();
	}
	int affectCols = pstm->executeUpdate();
	return affectCols;
}

int Mysql::del(std::string sql){
	return this->del(this->prepare(sql));
}

int Mysql::del(std::shared_ptr<sql::PreparedStatement> pstm){
	if(this->conn == NULL){
		this->connect();
	}
	int affectCols = pstm->executeUpdate();
	return affectCols;
}

        
