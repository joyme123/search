#include"DocumentDAO.h"

DocumentDAO::DocumentDAO(){
	google::InitGoogleLogging("1");
}
/**
 * insert a docuemnt into database and return id of this
 * @param document  add document into database(maybe use fastfs to storage)
 * @return id of this document
 */
int DocumentDAO::addDocument(Document document){
    string sql = "INSERT INTO "+TABLE+" (type,title,abstract,url,author,text,wordNum,updateTime,createTime)VALUES(?,?,?,?,?,?,?,?,?)";
    int id;
    try{
        Mysql mysql;
        shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setInt(1,document.type);
        pstm->setString(2,WstringToString(document.title));
        pstm->setString(3,WstringToString(document.abstract));
        pstm->setString(4,WstringToString(document.url));
        pstm->setString(5,WstringToString(document.author));
		pstm->setString(6,WstringToString(document.text));
        pstm->setUInt(7,document.wordNum);
        pstm->setDateTime(8,sql::SQLString(WstringToString(document.saveTime)));
        pstm->setDateTime(9,sql::SQLString(WstringToString(document.createTime)));
        id = mysql.insert(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "DocumentDAO->addDocument(Document document):"<< e.getErrorCode()<<"--"<<e.what();
    }
    return id;
}

/**
 * delete the document with an id
 * @param id document id
 * @return affect rows count
 */
int DocumentDAO::deleteDocument(int id){
    string sql = "DELETE FROM"+ TABLE +"WHERE id = ?";
    int rows;
    try{
        Mysql mysql;
        shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setInt(1,id);
        rows = mysql.del(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "DocumentDAO->deleteDocument(int id):" << e.getErrorCode()<<"--"<<e.what() << e.getSQLState();
        rows = -1;
    }
    return rows;
}

/**
 * parse the docment the put words of this document into database
 * each word generate a record reference document id
 * @param document the document to parse
 * @return affect rows count
 */
int DocumentDAO::parseDocumentAndUpdate(Document document){
    
}

