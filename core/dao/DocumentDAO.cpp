#include"DocumentDAO.h"

/**
 * insert a docuemnt into database and return id of this
 * @param document  add document into database(maybe use fastfs to storage)
 * @return id of this document
 */
int DocumentDAO::addDocument(Document document){
    string sql = "INSERT INTO "+TABLE+" (type,title,abstract,url,author,wordNum,saveTime,createTime)VALUES(%1,%2,%3,%4,%5,%6,%7,%8)";
    int id;
    try{
        Mysql mysql;
        shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setInt(1,document.type);
        pstm->setString(2,document.title);
        pstm->setString(3,document.abstract);
        pstm->setString(4,document.url);
        pstm->setString(5,document.author);
        pstm->setUInt(6,document.wordNum);
        pstm->setDateTime(7,document.saveTime);
        pstm->setDateTime(8,document.createTime);
        id = mysql.insert(pstm);
    }catch(sql::SQLException e){
        printSqlError(e);
        id = -1;
    }
    return id;
}

/**
 * delete the document with an id
 * @param id document id
 * @return affect rows count
 */
int DocumentDAO::deleteDocument(int id){
    string sql = "DELETE FROM"+ TABLE +"WHERE id = %1";
    int rows;
    try{
        Mysql mysql;
        shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setInt(1,id);
        rows = mysql.del(pstm);
    }catch(sql::SQLException e){
        cout << e.getErrorCode() << e.what() << endl;
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

