#include"DocumentController.h"

int DocumentController::documentEntry(std::wstring documentFormat)
{
    Document document = DocumentParser::documentFormat(documentFormat);
	DocumentDAO doc;
    doc.beginTransaction();         //begin transaction
    
    int id = doc.addDocument(document);
    if(id == -1){
     //add document failed
        LOG(ERROR) << "DocumentController->doucmentEntry(std::wstring documentFormat):add document failed";
        doc.rollback();
        return -1;
    }
 	document.id = id;
    
    
	std::map<std::wstring,std::vector<int> > map = DocumentParser::splitWord(document.text,__FRISO_COMPLEX_MODE__);
    
    int wordCount = 0;
    
	WordDAO wordDao;
	for(std::map<std::wstring,std::vector<int> >::iterator it = map.begin(); it != map.end(); it++){
        std::wstring word = it->first;
        
        PostingList posts;
        posts.document = document;
        posts.positions = it->second;
        
        //if the word exist,update it invertedHashIndex,else add the word
        int wordId = wordDao.isWordExist(WstringToString(word));    //-1 means not exist
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

