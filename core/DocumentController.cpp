#include"DocumentController.h"

int DocumentController::formatedDocumentEntry(std::string formatedDocument)
{
    Document document = DocumentParser::documentFormat(formatedDocument);
	DocumentDAO doc;
    doc.beginTransaction();         //begin transaction
    
    int id = doc.addDocument(document);
    if(id == -1){
     //add document failed
        LOG(ERROR) << "DocumentController->doucmentEntry(std::string formatedDocument):add document failed";
        doc.rollback();
        return -1;
    }
 	document.id = id;
    
    
	std::map<std::string,std::vector<int> > map = DocumentParser::splitWord(document.text,__FRISO_COMPLEX_MODE__);
    
    int wordCount = 0;
    
	WordDAO wordDao;
	for(std::map<std::string,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
        std::string word = it->first;
        
        PostingList posts;
        posts.documentId = document.id;
        posts.positions = it->second;
        
        //if the word exist,update it invertedHashIndex,else add the word
        int wordId = wordDao.isWordExist(word);    //-1 means not exist
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
	return wordCount;
}

int DocumentController::documentEntry(std::vector<Package> packs){
    return 0;
}

std::vector< Document > DocumentController::searchDocument(std::vector< unsigned int > documentId)
{
	DocumentDAO documentDao;
	return documentDao.searchDocument(documentId);
}


