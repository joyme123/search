#include "SortedHeap.h"

template<typename T>
SortedHeap<T>::SortedHeap(std::function<void(T&,T&)> cmp){
    this->cmp = cmp;
}

template<typename T>
void swap(T& t1,T& t2){
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}

template<typename T>
void SortedHeap<T>::adjustAfterInsert(){
    int last = this->heap.size() - 1;
    int flag = true;
    //从插入的节点位置开始向上调整
    while(last > 0 && flag){
        T child = this->heap[last];
        T parent = this->heap[(last - 1) / 2];
        if(this->cmp(child,parent)){
            this->swap(this->heap[(last - 1) / 2],this->heap[last]);
        }else{
            //不需要调整了
            flag = false;
        }
        last = (last - 1) / 2;
    }
}

template<typename T>
void SortedHeap<T>::adjustAfterDelete(int pos){
    //从pos位置开始向下调整
    int last = this->heap.size() - 1;
    bool flag = true;   //标记是否需要调整
    while(pos <= (last - 1) / 2 && flag){
        //一直调整到最后一个非叶子结点
        int topNum = 0;     //记录最小的结点编号

        T parent = this->heap[pos];
        T leftChild = this->heap[(pos + 1) * 2 - 1];    //(pos + 1) * 2 - 1避免了0的问题
        if(this->cmp(leftChild,parent)){
            topNum = (pos + 1) * 2 - 1;
        }else{
            topNum = pos;
        }
        
        if((pos + 1) * 2 <= last){
            //如果存在右结点
            T rightChild = this->heap[(pos + 1) * 2];
            if(this->cmp(rightChild,this->heap[topNum])){
                topNum = (pos + 1) * 2;
            }
        }

        //看看topNum是不是自己
        if(pos == topNum){
            //是自己就不用调整了
            flag = false;
        }else{
            //交换
            this->swap(this->heap[pos],this->heap[topNum]);
        }
    }
}

template<typename T>
int SortedHeap<T>::insertNode(T& node){
    this->heap.push_back(node);     //先将node放在最后一位
    if(this->heap.size() != 1){
        //如果大小不等于1，则在新增节点后调整
        this->adjust();
    }
}


template<typename T>
void SortedHeap<T>::deleteNode(int id){
    int last = this->heap.size() - 1;
    //与最后一个交换
    swap(this->heap[last],this->heap[id]);
    //删除最后一个
    this->heap.pop_back();      

    this->adjustAfterDelete(id);
    
}

template<typename T>
T SortedHeap<T>::popTopNode(){
    T top = this->heap[0];
    this->deleteNode(0);
    return top;
}

template<typename T>
T SortedHeap<T>::getTopNode(){
    return this->heap[0];
}

