#include"../core/PostingList.h"
#include<iostream>

using namespace std;

void printPostingList(std::shared_ptr<PostingList> p){
    //这里不能改变p的指针，否则会p的指向被改变，内存会泄露
	while(p!=NULL){
        cout << p->documentId;
        p = p->next;
    }
}

int main(){
    string postStr = "(10109,1)<39>(10111,1)<39>(10113,1)<39>";
    PostingList* ptl = new PostingList;
	ptl->generate(postStr);
    std::shared_ptr<PostingList> p(ptl);
    printPostingList(p);
    return 0;
}
