/**
 * filename:SimHashDAO.cpp
 * SimHash数据库查询类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"SimHashDAO.h"

int SimHashDAO::addSimHash(SimHash simHash){
    std::string sql = "INSERT INTO "+TABLE+" (id,simhash,docIds,createTime,updateTime,)VALUES(?,?,?,?,?)";
    int id = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setUInt(1,simHash.id);
        pstm->setString(2,simHash.simHash);
        pstm->setString(3,simHash.docIds);
        pstm->setString(4,simHash.createTime);
        pstm->setString(5,simHash.updateTime);
        id = this->mysql->insert(pstm);
    }catch(sql::SQLException &e){
        id = -1;
		LOG(ERROR) << "SimHashDAO->addSimHash(SimHash simHash):"<< e.getErrorCode()<<"--"<<e.what();
    }
    return id;
}

int SimHashDAO::deleteSimHash(unsigned int id){
    std::string sql = "DELETE FROM "+TABLE+" WHERE id = ?";
    int row = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setUInt(1,id);
        row = this->mysql->insert(pstm);
    }
}

int SimHashDAO::parseSimHashAndUpdate(SimHash simHash){

}
