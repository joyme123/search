/**
 * filename:DocumentDAO.cpp
 * 文档查询类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"DocumentDAO.h"

DocumentDAO::DocumentDAO(Mysql* mysql){
	this->mysql = mysql;
}
/**
 * insert a docuemnt into database and return id of this
 * @param document  add document into database(maybe use fastfs to storage)
 * @return id of this document, -1 means some error occured
 */
int DocumentDAO::addDocument(Document document){
    std::string sql = "INSERT INTO "+TABLE+" (type,title,abstract,url,author,text,wordNum,updateTime,createTime)VALUES(?,?,?,?,?,?,?,now(),now())";
    int id = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setUInt(1,document.type);
        pstm->setString(2,document.title);
        pstm->setString(3,document.abstract);
        pstm->setString(4,document.url);
        pstm->setString(5,document.author);
		pstm->setString(6,document.text);
        pstm->setUInt(7,document.wordNum);
        //pstm->setDateTime(8,sql::SQLString(document.updateTime));
        //pstm->setDateTime(9,sql::SQLString(document.createTime));
		std::cout << "正在写入文档......" << std::endl;
        id = this->mysql->insert(pstm);
    }catch(sql::SQLException &e){
        id = -1;
		LOG(ERROR) << "DocumentDAO->addDocument(Document document):"<< e.getErrorCode()<<"--"<<e.what();
    }
    return id;
}

/**
 * delete the document with an id
 * @param id document id
 * @return affect rows count, -1 means some error occured
 */
int DocumentDAO::deleteDocument(unsigned int id){
    std::string sql = "DELETE FROM"+ TABLE +"WHERE id = ?";
    int rows = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setInt(1,id);
        rows = this->mysql->del(pstm);
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
    return 0;
}

std::vector< Document > DocumentDAO::searchDocument(std::vector<unsigned int > documentId)
{
	std::vector<Document> documents;
	std::string sql = "SELECT id,title,type,abstract,url,author,text,wordNum,createTime,updateTime FROM " + this->TABLE;

	//如果没有搜索到相关的文章
	if(documentId.size() == 0){
		return documents;	//直接返回
	}

	std::string where = " WHERE id = " + std::to_string(documentId[0]);
	for(unsigned int i =1; i < documentId.size(); i++){
		where = where + " OR id = " + std::to_string(documentId[i]);
	}
	sql = sql + where;
	try{
		std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
		std::shared_ptr<sql::ResultSet> res = this->mysql->query(pstm);
		while(res->next()){
			Document document;
			document.id = res->getUInt("id");
			document.abstract = res->getString("abstract");
			document.title = res->getString("title");
			document.type = Document::getDocType(res->getInt("type"));
			document.url = res->getString("url");
			document.author = res->getString("author");
			document.text = res->getString("text");
			document.wordNum = res->getUInt("wordNum");
			document.createTime = res->getString("createTime");
			document.updateTime = res->getString("updateTime");
			documents.push_back(document);
		}
	}catch(sql::SQLException &e){
		LOG(ERROR) << "DocumentDAO->searchDocument(int id):" << e.getErrorCode()<<"--"<<e.what();
	}
	return documents;
}


