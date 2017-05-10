#include <iostream>
#include <functional>
#include "src/core/util/SortedHeap.hpp"

using namespace std;

int main(){
    std::function<bool(double&,double&)> cmp = [](double& a,double& b){
        return a < b;
    };

    SortedHeap<double> heap(cmp);
    double i = 20;
    double j = 20;
    double k = 20;
    double n = 20;
    double l = 19;
    double m = 10;
    double o = 5;
    double p = 1;


    heap.insertNode(i);
    heap.insertNode(j);
    heap.insertNode(k);
    heap.insertNode(n);
    int id = heap.insertNode(l);
    heap.insertNode(m);
    heap.insertNode(o);
    heap.insertNode(p);        //应该删掉1

    heap.deleteNode(id);

    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
    cout << heap.popTopNode() << endl;
}