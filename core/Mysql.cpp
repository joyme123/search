#include"Mysql.h"

void Mysql:: connect(){
	if(conn == NULL){
		std::shared_ptr<sql::Connection> temp(this->driver->connect(this->url,this->user,this->pass));
		this->conn = temp;
		std::shared_ptr<sql::Statement> stm(this->conn->createStatement()); 
		stm->execute("use "+database);
	}
}
Mysql::Mysql(){
	//get the instance of driver int construct function
	user = "5019";
	pass = "5019";
	database = "empdb";
	url = "tcp://115.29.114.202:3306";
	this->driver = sql::mysql::get_driver_instance();
}
        
std::shared_ptr<sql::Connection> Mysql:: getConnection(){
	if(conn == NULL){
		this->connect();
	}
	return this->conn;
}
        

std::shared_ptr<sql::PreparedStatement> Mysql:: prepare(std::string str){
	if(conn == NULL){
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
	if(conn == NULL){
		this->connect();
	}
	std::shared_ptr<sql::ResultSet> res(pstm->executeQuery());
	return res;    
}

int Mysql:: insert(std::string sql){
	return this->insert(this->prepare(sql));
}
        

int Mysql:: insert(std::shared_ptr<sql::PreparedStatement> pstm){
	if(conn == NULL){
		this->connect();
	}
	pstm->executeQuery();
	//last_insert_id(在多个数据库连接下安全)
	sql::ResultSet*  res = this->prepare("select last_insert_id()")->executeQuery();
	int id = -1;
	if(res->next())
			id = res->getInt(1);
	return id;
}
        

int Mysql::update(std::string sql){
	return this->update(this->prepare(sql));
}

int Mysql::update(std::shared_ptr<sql::PreparedStatement> pstm){
	if(conn == NULL)
		this->connect();
	int affectCols = pstm->executeUpdate();
	return affectCols;
}

int Mysql::del(std::string sql){
	return this->del(this->prepare(sql));
}

int Mysql::del(std::shared_ptr<sql::PreparedStatement> pstm){
	if(conn == NULL)
		this->connect();
	int affectCols = pstm->executeUpdate();
	return affectCols;
}

        
