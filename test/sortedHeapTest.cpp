#include <iostream>
#include <functional>
#include "src/core/util/SortedHeap.hpp"

using namespace std;

int main(){
    std::function<bool(double&,double&)> cmp = [](double& a,double& b){
        return a < b;
    };

    SortedHeap<double> heap(cmp);
    double i = 10;
    double j = 11;
    double k = 5;
    double n = 5;
    double l = 5;
    double m = 5;
    double o = 5;
    double p = 5;
    double q = 5;
    double r = 5;
    double s = 15;
    double t = 25;


    heap.insertNode(i);
    int id = heap.insertNode(j);
    heap.insertNode(k);
    heap.insertNode(n);
    heap.insertNode(l);
    heap.insertNode(m);
    heap.insertNode(o);
    heap.insertNode(p);       
    heap.insertNode(q);   
    heap.insertNode(r);   
    heap.insertNode(s);   
    heap.insertNode(t);   

    heap.deleteNode(id);

    std::unique_ptr<double> res;

    while((res = heap.popTopNode()) != nullptr)
        cout << *(res.get()) << endl;


}