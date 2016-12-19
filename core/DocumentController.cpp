#include"DocumentController.h"

int DocumentController::formatedDocumentEntry(std::string formatedDocument)
{
    Document document = DocumentParser::documentFormat(formatedDocument);
	DocumentDAO doc;
    int wordCount = 0;
    try{
        doc.beginTransaction();                 //事务开启
        
        int id = doc.addDocument(document);     //将文档存入数据库
        if(id == -1){
        //文档存储失败
            LOG(ERROR) << "DocumentController->doucmentEntry(std::string formatedDocument):add document failed";
            doc.rollback();
            return -1;
        }
        document.id = id;
        
        //分词
        std::map<std::string,std::vector<int> > map = DocumentParser::splitWord(document.text,__FRISO_COMPLEX_MODE__);  
        
        WordDAO wordDao;
        //循环写入单词
        for(std::map<std::string,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
            std::string word = it->first;
            
            PostingList posts;
            posts.documentId = document.id;
            posts.positions = it->second;
            
            //检查单词是否存在数据库中，如果存在，则更新postIndex，否则添加新的单词到数据库
            int wordId = wordDao.isWordExist(word);    //-1代表不存在该单词
            std::shared_ptr<PostingList> ppp = std::make_shared<PostingList>(posts);
            if(wordId == -1){
                if(wordDao.addWord(word,ppp)<0){
                    doc.rollback();
                }else{
                    wordCount++;
                }
            }else{
                if(wordDao.updateWord(wordId,ppp)<0){
                    doc.rollback();   
                }else{
                    wordCount++;
                }
            }
        }
        
        doc.commit();          //commit transaction
    }catch(std::exception &e){
        doc.rollback();
    }
	return wordCount;
}

int DocumentController::documentEntry(std::vector<Package> packs){

    FrequencyDictSingleton *frequencyDictInstance = FrequencyDictSingleton::getInstance();      //获取词频表的单例
    StopWordDictSingleton *stopWordDictInstance = StopWordDictSingleton::getInstance();         //获取停顿词的单例
    DocumentParser docParser;
    DocumentAnalysis docAnalysis;
    SimHash simHash;
    int wordCount = 0;

    for(auto it = packs.begin(); it != packs.end(); it++){

        std::string content = (*it).content;
        std::string formatedContent = docAnalysis.htmlFormat(content);        //经过处理的文本，去除了噪声
        std::string peeledHtml = docAnalysis.htmlPeel(formatedContent);       //统一去除所有的标签
        std::string mainContent = docAnalysis.fastHtmlAnalysis(peeledHtml);   //提取出网页正文

        std::map<std::string,std::vector<int> > resultMap =  DocumentParser::splitWord(mainContent,__FRISO_COMPLEX_MODE__);    //得到正文的分词结果
        std::map<std::string,std::vector<int> > removedResultMap = simHash.removeStopWord(resultMap,stopWordDictInstance->stopWordDict);//移除stopWord   
        std::bitset<SimHash::BITSET_LENGTH> bitset = simHash.calculate(removedResultMap,frequencyDictInstance->frequencyDict);     //计算特征码

        std::cout << bitset << std::endl;

        Document document = docParser.documentFormat(*it);
        DocumentDAO doc;
        try{
            doc.beginTransaction();                 //事务开启
            
            int id = doc.addDocument(document);     //将文档存入数据库
            if(id == -1){
            //文档存储失败
                LOG(ERROR) << "DocumentController->doucmentEntry(std::string formatedDocument):add document failed";
                doc.rollback();
                return -1;
            }
            document.id = id;
            
            //对去掉标签的网页全文分词
            std::map<std::string,std::vector<int> > map = DocumentParser::splitWord(peeledHtml,__FRISO_COMPLEX_MODE__);  
            
            WordDAO wordDao;
            //循环写入单词
            for(std::map<std::string,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
                std::string word = it->first;
                
                PostingList posts;
                posts.documentId = document.id;
                posts.positions = it->second;
                
                //检查单词是否存在数据库中，如果存在，则更新postIndex，否则添加新的单词到数据库
                int wordId = wordDao.isWordExist(word);    //-1代表不存在该单词
                std::shared_ptr<PostingList> ppp = std::make_shared<PostingList>(posts);
                if(wordId == -1){
                    if(wordDao.addWord(word,ppp)<0){
                        doc.rollback();
                    }else{
                        wordCount++;
                    }
                }else{
                    if(wordDao.updateWord(wordId,ppp)<0){
                        doc.rollback();   
                    }else{
                        wordCount++;
                    }
                }
            }
            
            doc.commit();          //commit transaction
        }catch(std::exception &e){
            doc.rollback();
        }
    }   //end for 
	return wordCount;
}

std::vector< Document > DocumentController::searchDocument(std::vector< unsigned int > documentId)
{
	DocumentDAO documentDao;
	return documentDao.searchDocument(documentId);
}


