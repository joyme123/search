/**
 * filename:PostingList.cpp
 * 倒排列表的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include"PostingList.h"

PostingList::PostingList(){
    
}


void PostingList::generate(std::string postingListStr){
    /*
     * (docId,count)<pos1,pos2,pos3>
     * 
     */
    int id = -1;
    //int count = -1;
    std::vector<int> tmpPositions;
    std::string idStr;
    std::vector<char> save;
    int times = 0;        //, 
    std::shared_ptr<PostingList> current;
    bool first = true;
    for(int i = 0; postingListStr[i] != '\0'; i++){
        if(postingListStr[i] == ','&&times == 0){
            //doc id
            id = VectorToInt(save);
            save.clear();
            times++;
        }else if(postingListStr[i] == ')'){
            //word count
            //count = VectorToInt(save);
            save.clear();
            
        }else if(postingListStr[i] == '<' || postingListStr[i] == '('){
            
        }else if(postingListStr[i] == ','&&times > 0){
            //pos
            tmpPositions.push_back(VectorToInt(save));
            save.clear();
            times++;
        }else if(postingListStr[i] == '>'){
            //postingList end
            tmpPositions.push_back(VectorToInt(save));
            save.clear();
            times++;
            PostingList *tmp = new PostingList;
            std::shared_ptr<PostingList> next(tmp);
            
            if(first){
                this->documentId = id;
                this->positions = tmpPositions;
                
                if(postingListStr[i+1] != '\0'){
                    this->next = next;
                }else{
                    this->next = NULL;
                }
                first = false;
            }else{
                current->documentId = id;
                current->positions = tmpPositions;
                if(postingListStr[i+1] != '\0'){
                    current->next = next;
                }else{
                    current->next = NULL;
                }
            }
            current = next;
            times = 0;
            tmpPositions.clear();
        }else{
            save.push_back(postingListStr[i]);
        }
    }
}


std::vector<unsigned int> PostingList::toVector(){
	std::vector<unsigned int> ids;
    std::shared_ptr<PostingList> p = this->next;
    ids.push_back(this->documentId);
	while(p != NULL){
		ids.push_back(p->documentId);
        p = p->next;
    }
    return ids;
}
