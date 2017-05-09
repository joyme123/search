#include <iostream>
#include <functional>
#include "src/core/util/SortedHeap.h"

using namespace std;

int main(){
    std::function cmp = [](int& a,int& b){
        return a < b;
    }

    SortedHeap<int> heap(cmp);
    heap.insertNode(1);
    heap.insertNode(10);
    heap.insertNode(20);
    heap.insertNode(5);

    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
}