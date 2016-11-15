#include"WordDAO.h"

/**
 * insert the word and it's InvertedIndexHash
 * @param word add word into database with it InvertedIndexHash
 * @param indexHash InvertedIndexHash of word
 * @return the added record id
 */
int WordDAO::addWord(Word word, InvertedIndexHash indexHash){
    string sql = "INSERT INTO" + TABLE + "(word,postingList,docsCount,totalCount)VALUES(%1,%2,%3,%4)";
    std::tr1::shared_ptr<PostingList> postingList = indexHash.postingList;
    string list;
    bool first = true;      //it's first time to construct list
    while(postingList != NULL){
        vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+to_string(postingList->document.id)+","+to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+to_string(postingList->document.id)+","+to_string(positions.size())+")";
        }
        string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = to_string(*it);
                firstC = false;
            }else{
                position = position + "," +to_string(*it);
            }
        }
        position = ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
            
        postingList = postingList->next;
    }
    int id;
    try{
        Mysql mysql;
        std::tr1::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setString(1,word.text);
        pstm->setString(2,list);
        pstm->setUInt64(3,indexHash.docsCount);
        pstm->setUInt64(4,indexHash.totalCount);
        id = mysql.insert(pstm);
    }catch(sql::SQLException e){
        printSqlError(e);
        id = -1;
    }
    return id;
}

    /**
     * delete a record of the word by id
     * @param id word id
     * @return affect rows num
     */
int WordDAO::deleteWord(unsigned int id){
    string sql = "DELETE FROM " + TABLE + " WHERE id = %1";
    int rows;
    try{
        Mysql mysql;
        std::tr1::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setUInt(1,id);
        rows = mysql.del(pstm);
    }catch(sql::SQLException e){
        printSqlError(e);
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
    string sql = "UPDATE " + TABLE + " as w set w.postingList = CONCAT(w.postingList,'%1'),docsCount = w.docsCount + '%2',totalCount = w.totalCount + '%3' where id = %4";
    std::tr1::shared_ptr<PostingList> postingList = indexHash.postingList;
    string list;
    bool first = true;      //it's first time to construct list
    while(postingList != NULL){
        vector<int> positions = postingList->positions;
        
        if(first){
            list = "("+to_string(postingList->document.id)+","+to_string(positions.size())+")";
            first = false;
        }else{
            list = list + "|("+to_string(postingList->document.id)+","+to_string(positions.size())+")";
        }
        string position = "<";
        bool firstC = true; //it is first time to construct position info
        for(std::vector<int>::iterator it = positions.begin();it != positions.end();it++){
            if(firstC){
                position = to_string(*it);
                firstC = false;
            }else{
                position = position + "," +to_string(*it);
            }
        }
        position = ">";
        list = list + position;     //(documentId,frequency)<pos1,pos2,pos3>
            
        postingList = postingList->next;
    }
    int rows;
    try{
        Mysql mysql;
        std::tr1::shared_ptr<sql::PreparedStatement> pstm = mysql.prepare(sql);
        pstm->setString(1,list);
        pstm->setUInt64(2,indexHash.docsCount);
        pstm->setUInt64(3,indexHash.totalCount);
        pstm->setUInt(4,id);
        rows = mysql.update(pstm);
    }catch(sql::SQLException e){
        printSqlError(e);
        rows = -1;
    }
    return rows;
}

