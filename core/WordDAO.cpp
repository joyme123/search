#include"WordDAO.h"

/**
 * construct for WordDAO
 */
WordDAO::WordDAO(){
	google::InitGoogleLogging("1");
}

/**
 * insert the word and it's InvertedIndexHash
 * @param word add word into database with it InvertedIndexHash
 * @param indexHash InvertedIndexHash of word
 * @return the added record id,-1 indicate failed
 */
int WordDAO::addWord(Word word, InvertedIndexHash indexHash){
	std::string TABLE;
	if(indexHash.type == ngramWord){
		TABLE = NGRAMTABLE;
	}else if(indexHash.type == splitWord){
		TABLE = SPLITTABLE;
	}else{
		LOG(ERROR) << "WordDAO->addWord(Word word, InvertedIndexHash indexHash):" << "param type not exist";
		return -1;
	}
    std::string sql = "INSERT INTO" + TABLE + "(word,postingList,docsCount,totalCount)VALUES(?,?,?,?)";
    std::shared_ptr<PostingList> postingList = indexHash.postingList;
    std::string list;
    bool first = true;      //it's first time to construct list
    while(postingList != NULL){
        std::vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+std::to_string(postingList->document.id)+","+std::to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+std::to_string(postingList->document.id)+","+std::to_string(positions.size())+")";
        }
        std::string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = std::to_string(*it);
                firstC = false;
            }else{
                position = position + "," +std::to_string(*it);
            }
        }
        position = ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
            
        postingList = postingList->next;
    }
    int id;
    try{
        Mysql mysql;
        std::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setString(1,WstringToString(word.text));
        pstm->setString(2,list);
        pstm->setUInt64(3,indexHash.docsCount);
        pstm->setUInt64(4,indexHash.totalCount);
        id = mysql.insert(pstm);
    }catch(sql::SQLException e){
		LOG(ERROR) << "WordDAO->addWord(Word word, InvertedIndexHash indexHash):"<< e.getErrorCode()<<"--"<<e.what();
        id = -1;
    }
    return id;
}

    /**
     * delete a record of the word by id
     * @param id word id
     * @return affect rows num
     */
int WordDAO::deleteWord(unsigned int id,InvertHashIndexType type){
	std::string TABLE;
	if(type == ngramWord){
		TABLE = NGRAMTABLE;
	}else if(type == splitWord){
		TABLE = SPLITTABLE;
	}else{
		LOG(ERROR) << "WordDAO->deleteWord(unsigned int id,InvertHashIndexType type):"<< "param type not exist";
		return -1;
	}
    std::string sql = "DELETE FROM " + TABLE + " WHERE id = ?";
    int rows;
    try{
        Mysql mysql;
        std::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setUInt(1,id);
        rows = mysql.del(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "WordDAO->deleteWord(unsigned int id,InvertHashIndexType type):"<< e.getErrorCode()<<"--"<<e.what();
        rows = -1;
    }
    return rows;
}


    /**
     * update a word's InvertedIndexHash
     * @param id the word id
     * @param indexHash InvertedIndexHash of the word
     * @return affect rows
     */
int WordDAO::updateWordInvertHash(unsigned int id, InvertedIndexHash indexHash){
	std::string TABLE;
	if(indexHash.type == ngramWord){
		TABLE = NGRAMTABLE;
	}else if(indexHash.type == splitWord){
		TABLE = SPLITTABLE;
	}else{
		LOG(ERROR) << "WordDAO->updateWordInvertHash(unsigned int id, InvertedIndexHash indexHash):" << "param type not exist";
		return -1;
	}
	
    std::string sql = "UPDATE " + TABLE + " as w set w.postingList = CONCAT(w.postingList,'?'),docsCount = w.docsCount + '?',totalCount = w.totalCount + '?' where id = ?";
    std::shared_ptr<PostingList> postingList = indexHash.postingList;
    std::string list;
    bool first = true;      //it's first time to construct list
    while(postingList != NULL){
        std::vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+std::to_string(postingList->document.id)+","+std::to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+std::to_string(postingList->document.id)+","+std::to_string(positions.size())+")";
        }
        std::string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = std::to_string(*it);
                firstC = false;
            }else{
                position = position + "," +std::to_string(*it);
            }
        }
        position = ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
            
        postingList = postingList->next;
    }
    int rows;
    try{
        Mysql mysql;
        std::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setString(1,list);
        pstm->setUInt64(2,indexHash.docsCount);
        pstm->setUInt64(3,indexHash.totalCount);
        pstm->setUInt(4,id);
        rows = mysql.update(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "WordDAO->updateWordInvertHash(unsigned int id, InvertedIndexHash indexHash):"<< e.getErrorCode()<<"--"<<e.what();
        rows = -1;
    }
    return rows;
}

