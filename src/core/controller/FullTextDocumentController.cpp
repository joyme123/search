#include "src/core/controller/FullTextDocumentController.h"

int FullTextDocumentController::documentEntry(std::string documentStr){
    unsigned int wordCount = 0;
    Mysql mysql = this->pool->getConnection();
    Document document = DocumentParser::documentJsonFormat(documentStr);
    FrequencyDictSingleton *frequencyDictInstance = FrequencyDictSingleton::getInstance();      //获取词频表的单例
    StopWordDictSingleton *stopWordDictInstance = StopWordDictSingleton::getInstance();         //获取停顿词的单例
    WordSplitSingleton *wordSplit = WordSplitSingleton::getInstance(__FRISO_COMPLEX_MODE__);    //分词的单例
    std::map<std::string,std::vector<int> > resultMap =  wordSplit->splitWord(document.text);    //得到正文的分词结果

    SimHashCal simHashCal;
    std::map<std::string,std::vector<int> > removedResultMap = simHashCal.removeStopWord(resultMap,stopWordDictInstance->stopWordDict);//移除stopWord   
    std::bitset<SimHashCal::BITSET_LENGTH> bitset = simHashCal.calculate(removedResultMap,frequencyDictInstance->frequencyDict);     //计算特征码

    std::cout <<"FullTextDocumentController.cpp 104行:计算出simHash特征码为"<<bitset << std::endl;
    document.wordNum = resultMap.size();

    DocumentDAO doc(&mysql);
    try{
        std::cout << "开启事务" << std::endl;
        mysql.beginTransaction();                 //事务开启
        
        int id = doc.addDocument(document);     //将文档存入数据库
        if(id == -1){
        //文档存储失败
            LOG(ERROR) << "FullTextDocumentController->doucmentEntry(std::string formatedDocument):add document failed";
            mysql.rollback();
            this->pool->retConnection(mysql);
            return -1;
        }
        document.id = id;
        
        WordDAO wordDao(&mysql);
        //循环写入单词
        for(std::map<std::string,std::vector<int> >::iterator it = resultMap.begin(); it != resultMap.end(); it++){
            std::string word = it->first;
            
            PostingList posts;
            posts.documentId = document.id;
            posts.positions = it->second;
            
            std::shared_ptr<PostingList> ppp = std::make_shared<PostingList>(posts);

            if(wordDao.addOrUpdateWord(word,ppp)<0){
                mysql.rollback();
                this->pool->retConnection(mysql);
                return -1;
            }else{
                wordCount++;
            }

        }
        
        mysql.commit();          //commit transaction
        std::cout << "提交事务" << std::endl;
        this->pool->retConnection(mysql);
    }catch(sql::SQLException &e){
        mysql.rollback();
        LOG(ERROR) << "FullTextDocumentController->documentEntry(std::vector<Package> packs):"<< e.getErrorCode()<<"--"<<e.what();
    }

	return wordCount;
    return 0;
}