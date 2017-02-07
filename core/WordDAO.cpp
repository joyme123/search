/**
 * filename:WordDAO.cpp
 * 单词查询类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"WordDAO.h"

/**
 * construct for WordDAO
 */
WordDAO::WordDAO(Mysql* mysql){
	this->mysql = mysql;
}

/**
 * insert the word and it's InvertedIndexHash
 * @param word add word into database with it InvertedIndexHash
 * @param postingList postingList of word
 * @return the added record id,-1 indicate failed
 */
int WordDAO::addWord(Word word, std::shared_ptr<PostingList> postingList){
	std::string TABLE = "word";
// 	if(indexHash.type == ngramWord){
// 		TABLE = NGRAMTABLE;
// 	}else if(indexHash.type == splitWord){
// 		TABLE = SPLITTABLE;
// 	}else{
// 		LOG(ERROR) << "WordDAO->addWord(Word word, InvertedIndexHash indexHash):" << "param type not exist";
// 		return -1;
// 	}
	
    std::string sql = "INSERT INTO " + TABLE + "(word,postingList,docCount,totalCount)VALUES(?,?,'1',?)";
    std::string list;
    bool first = true;      //it's first time to construct list
    unsigned long long count = 0;
    while(postingList != NULL){
        std::vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+std::to_string(postingList->documentId)+","+std::to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+std::to_string(postingList->documentId)+","+std::to_string(positions.size())+")";
        }
        std::string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = position + std::to_string(*it);
                firstC = false;
            }else{
                position = position + "," +std::to_string(*it);
            }
        }
        position = position +  ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
        
        count = count + postingList->positions.size();
        postingList = postingList->next;
		
    }
    int id = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setString(1,word.text);
        pstm->setString(2,list);
        pstm->setInt(3,count);
        id = mysql->insert(pstm);
    }catch(sql::SQLException &e){
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
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setUInt(1,id);
        rows = mysql->del(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "WordDAO->deleteWord(unsigned int id,InvertHashIndexType type):"<< e.getErrorCode()<<"--"<<e.what();
        rows = -1;
    }
    return rows;
}


    /**
     * update a word's InvertedIndexHash
     * @param id the word id
     * @param postingList InvertedIndexHash of the word
     * @return affect rows
     */
int WordDAO::updateWord(unsigned int id, std::shared_ptr<PostingList> postingList){
// 	std::string TABLE;
// 	if(indexHash.type == ngramWord){
// 		TABLE = NGRAMTABLE;
// 	}else if(indexHash.type == splitWord){
// 		TABLE = SPLITTABLE;
// 	}else{
// 		LOG(ERROR) << "WordDAO->updateWordInvertHash(unsigned int id, InvertedIndexHash indexHash):" << "param type not exist";
// 		return -1;
// 	}
	
    std::string sql = "UPDATE " + TABLE + " as w set w.postingList = CONCAT(w.postingList,?),w.docCount = w.docCount + ?,w.totalCount = w.totalCount + ? where id = ?";
    std::string list;
    bool first = true;      //it's first time to construct list
    unsigned long long wordCount = 0;
    int docCount = 0;       //docuemnt count
    while(postingList != NULL){
        std::vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+std::to_string(postingList->documentId)+","+std::to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+std::to_string(postingList->documentId)+","+std::to_string(positions.size())+")";
        }
        std::string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = position + std::to_string(*it);
                firstC = false;
            }else{
                position = position + "," +std::to_string(*it);
            }
        }
        wordCount = wordCount + postingList->positions.size();
        docCount++;
        position = position + ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
            
        postingList = postingList->next;
    }
    int rows = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare(sql);
        pstm->setString(1,list);
        pstm->setInt(2,docCount);
        pstm->setUInt64(3,wordCount);
        pstm->setUInt(4,id);
        rows = this->mysql->update(pstm);
    }catch(sql::SQLException &e){
		LOG(ERROR) << "WordDAO->updateWord(unsigned int id, std::shared_ptr<PostingList> postingList):"<< e.getErrorCode()<<"--"<<e.what();
        rows = -1;
    }
    return rows;
}

int WordDAO::isWordExist(std::string word){
    unsigned long long wordId = -1;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare("SELECT id FROM "+TABLE+" WHERE word = ?");
        pstm->setString(1,word);
        std::shared_ptr<sql::ResultSet> res = mysql->query(pstm);
        if(res->next()){
            wordId = res->getUInt64("id");
        }
    }catch(sql::SQLException &e){
        wordId = -1;
        LOG(ERROR) << "WordDAO->isWordExist(std::string word):"<< e.getErrorCode()<<"--"<<e.what();
    }
    
    return wordId;
}

InvertedIndexHash WordDAO::searchWord(std::string word){
    InvertedIndexHash indexHash;
    try{
        std::shared_ptr<sql::PreparedStatement> pstm = this->mysql->prepare("SELECT id,word,postingList,docCount,totalCount FROM "+TABLE+"  WHERE word = ?");
        pstm->setString(1,word);
        std::shared_ptr<sql::ResultSet> res = this->mysql->query(pstm);
        if(res->next()){
            indexHash.id = res->getInt("id");
            indexHash.type = splitWord;
            PostingList* p = new PostingList;
			p->generate(res->getString("postingList"));
            std::shared_ptr<PostingList> post(p);
            indexHash.postingList = post;
            indexHash.docCount = res->getUInt64("docCount");
            indexHash.totalCount = res->getUInt64("totalCount");
        }
    }catch(sql::SQLException &e){
        LOG(ERROR) << "WordDAO->searchWord(std::string word):"<< e.getErrorCode()<<"--"<<e.what();
    }
    
    return indexHash;
}

