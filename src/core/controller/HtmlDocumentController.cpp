#include "src/core/controller/HtmlDocumentController.h"

int HtmlDocumentController::documentEntry(std::string documentStr){
    Mysql mysql = this->pool->getConnection();
    FrequencyDictSingleton *frequencyDictInstance = FrequencyDictSingleton::getInstance();      //获取词频表的单例
    StopWordDictSingleton *stopWordDictInstance = StopWordDictSingleton::getInstance();         //获取停顿词的单例
    WordSplitSingleton *wordSplit = WordSplitSingleton::getInstance(__FRISO_COMPLEX_MODE__);
    DocumentParser docParser;
    DocumentAnalysis docAnalysis;
    SimHashCal simHashCal;
    int wordCount = 0;

    Document document = docParser.documentJsonFormat(documentStr);         //document对象
    std::string content = document.text;
    std::string formatedContent = docAnalysis.htmlFormat(content);          //经过处理的文本，去除了噪声
    std::string peeledHtml = docAnalysis.htmlPeel(formatedContent);         //统一去除所有的标签
    std::string mainContent = docAnalysis.fastHtmlAnalysis(peeledHtml);     //提取出网页正文

    std::map<std::string,std::vector<int> > resultMap =  wordSplit->splitWord(mainContent);    //得到正文的分词结果
    std::map<std::string,std::vector<int> > removedResultMap = simHashCal.removeStopWord(resultMap,stopWordDictInstance->stopWordDict);//移除stopWord   
    std::bitset<SimHashCal::BITSET_LENGTH> bitset = simHashCal.calculate(removedResultMap,frequencyDictInstance->frequencyDict);     //计算特征码

    std::cout <<"DocumentController.cpp 104行:计算出simHash特征码为"<<bitset << std::endl;

    document.text = peeledHtml;
    document.wordNum = resultMap.size();

    DocumentDAO doc(&mysql);
    try{
        std::cout << "开启事务" << std::endl;
        mysql.beginTransaction();                 //事务开启
        
        int id = doc.addDocument(document);     //将文档存入数据库
        if(id == -1){
        //文档存储失败
            LOG(ERROR) << "HTMLDocumentController->doucmentEntry(std::string formatedDocument):add document failed";
            mysql.rollback();
            this->pool->retConnection(mysql);
            return -1;
        }
        document.id = id;
        
        //对去掉标签的网页全文分词
        std::map<std::string,std::vector<int> > map = wordSplit->splitWord(peeledHtml);  
        
        WordDAO wordDao(&mysql);
        //循环写入单词
        for(std::map<std::string,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
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
        LOG(ERROR) << "HTMLDocumentController->documentEntry(std::vector<Package> packs):"<< e.getErrorCode()<<"--"<<e.what();
    }

	return wordCount;
}