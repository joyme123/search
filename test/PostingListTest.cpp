#include"../core/PostingList.h"
#include<iostream>

using namespace std;

void printPostingList(std::shared_ptr<PostingList> p){
    while(p!=NULL){
        cout << p->documentId;
        p = p->next;
    }
}

int main(){
    string postStr = "(10109,1)<39>(10111,1)<39>(10113,1)<39>";
    PostingList ptl(postStr);
    std::shared_ptr<PostingList> p(&ptl);
    printPostingList(p);
    return 0;
}
