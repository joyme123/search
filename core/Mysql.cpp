#include"Mysql.h"

void Mysql:: connect(){
	if(conn == NULL){
		std::shared_ptr<sql::Connection> temp(this->driver->connect(this->url,this->user,this->pass));
		this->conn = temp.get();
		std::shared_ptr<sql::Statement> stm(this->conn->createStatement()); 
		if(stm->execute("use "+database)){
			std::cout << "数据库连接成功";
		}else{
			std::cout << "数据库连接成功";
		}
	}
}
Mysql::Mysql(){
	//get the instance of driver int construct function
	this->user = "5019";
	this->pass = "5019";
	this->database = "empdb";
	this->url = "tcp://115.29.114.202:3306";
	this->driver = sql::mysql::get_driver_instance();
}

void Mysql::beginTransaction(){
    if(conn == NULL){
		this->connect();
	}
	this->conn->setAutoCommit(false);      //open transaction
}

void Mysql::commit(){
    if(conn == NULL){
		this->connect();
	}
	this->conn->commit();
    this->conn->setAutoCommit(true);
}


void Mysql::rollback(){
    if(conn == NULL){
		this->connect();
	}
	this->conn->rollback();
    this->conn->setAutoCommit(true);      //end transaction
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
	delete res;		//删除res指针指向的内存
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

        
