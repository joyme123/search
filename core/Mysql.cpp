#include"Mysql.h"

void Mysql::connect(){
	if(this->conn == NULL){
		this->conn = this->driver->connect(this->url,this->user,this->pass);
		std::shared_ptr<sql::Statement> stm(this->conn->createStatement()); 
		stm->execute("use "+this->database);
	}
}
Mysql::Mysql(){
	//get the instance of driver int construct function
	this->user = "5019";
	this->pass = "5019";
	this->database = "empdb";
	this->url = "tcp://115.29.114.202:3306";
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

        
