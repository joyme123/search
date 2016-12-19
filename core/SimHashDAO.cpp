#include"SimHashDAO.h"

int SimHashDAO::addSimHash(SimHash simHash){
    std::string sql = "INSERT INTO "+TABLE+" (type,title,abstract,url,author,text,wordNum,updateTime,createTime)VALUES(?,?,?,?,?,?,?,?,?)";
    int id = -1;
    try{
        //Mysql mysql;
        std::shared_ptr<sql::PreparedStatement> pstm = this->prepare(sql);
        pstm->setUInt(1,document.type);
        pstm->setString(2,document.title);
        pstm->setString(3,document.abstract);
        pstm->setString(4,document.url);
        pstm->setString(5,document.author);
		pstm->setString(6,document.text);
        pstm->setUInt(7,document.wordNum);
        pstm->setDateTime(8,sql::SQLString(document.updateTime));
        pstm->setDateTime(9,sql::SQLString(document.createTime));
        id = this->insert(pstm);
    }catch(sql::SQLException &e){
        id = -1;
		LOG(ERROR) << "DocumentDAO->addDocument(Document document):"<< e.getErrorCode()<<"--"<<e.what();
    }
    return id;
}
