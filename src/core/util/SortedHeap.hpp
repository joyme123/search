/**
 * 排序堆的实现
 * 堆使用的是完全二叉树的结构，使用数组（数组从零开始）保存，那么最后一个非叶子节点为(n - 1) / 2
 * 堆的构建一直都是在有序的基础上的，那么每次调整只需比较i和(i - 1) / 2的元素，依次上推
 * 支持任意类的排序
 * 当前还不支持多线程环境下的使用
 * author:jiangpengfie
 * date:2017-05-09
 */
#ifndef SORTEDHEAP_H
#define SORTEDHEAP_H
#include <iostream>
#include <vector>
#include <functional>
#include "src/core/util/util.h"


template<class T>
class SortedHeap{
    private:
        struct HeapNode{
            unsigned int id;
            T obj;
            HeapNode(unsigned int id,T t){
                this->id = id;
                this->obj = t;
            }
        };
        std::vector<HeapNode> heap;
        unsigned int autoIncrementId;
        std::function<bool(T& ,T&)> cmp;
        
        /**
         * 插入节点后调整堆中不符合的节点
         */
        void adjustAfterInsert();

        /**
         * pop出堆顶元素后调整堆中不符合的节点
         */
        void adjustAfterPopTop();

        /**
         * 删除节点后调整堆中不符合的节点
         * @param i 删除的节点id
         */
        void adjustAfterDelete(int id);         

        void swap(HeapNode& t1,HeapNode& t2);

        void deleteNodeByPos(const unsigned int pos);
    public:
        /**
         * 构造函数
         * @param cmp 用来比较
         */
        SortedHeap(std::function<bool(T&,T&)> cmp);
        /**
         * 插入节点
         * @param node 插入的节点
         */
        unsigned int insertNode(T& node);
        /**
         * 删除节点，时间复杂度为O(n)
         * @param id  要删除的节点id
         */
        void deleteNode(int id);
        
        /**
         * pop最小的节点
         * @return T 返回的最顶部的节点
         */
        T popTopNode();

        /**
         * 获取最顶部的节点
         * @return T 最顶部的节点
         */
        T getTopNode();

        /**
         * 删除顶部的节点
         *
         */
        void deleteTopNode();
};

template<typename T>
SortedHeap<T>::SortedHeap(std::function<bool(T&,T&)> cmp){
    this->cmp = cmp;
    this->autoIncrementId = 0;
}

template<typename T>
void SortedHeap<T>::swap(HeapNode& t1,HeapNode& t2){
    HeapNode tmp = t1;
    t1 = t2;
    t2 = tmp;
}

template<typename T>
void SortedHeap<T>::adjustAfterInsert(){
    int last = this->heap.size() - 1;
    int flag = true;
    //从插入的节点位置开始向上调整
    while(last > 0 && flag){
        if(this->cmp(this->heap[last].obj,this->heap[(last - 1) / 2].obj)){
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
    if(last == 0)
        return;     //最后一个不需要调整
    bool flag = true;   //标记是否需要调整
    while(pos <= (last - 1) / 2 && flag){
        //一直调整到最后一个非叶子结点
        int topNum = 0;     //记录最小的结点编号

          //(pos + 1) * 2 - 1是左孩子，pos是父
        if(this->cmp(this->heap[(pos + 1) * 2 - 1].obj,this->heap[pos].obj)){
            topNum = (pos + 1) * 2 - 1;
        }else{
            topNum = pos;
        }
        
        if((pos + 1) * 2 <= last){
            //如果存在右结点
            if(this->cmp(this->heap[(pos + 1) * 2].obj,this->heap[topNum].obj)){
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
unsigned int SortedHeap<T>::insertNode(T& node){
    HeapNode hNode(this->autoIncrementId++,node);
    this->heap.push_back(hNode);     //先将node放在最后一位
    if(this->heap.size() != 1){
        //如果大小不等于1，则在新增节点后调整
        this->adjustAfterInsert();
    }
    return this->autoIncrementId - 1;
}

template<typename T>
void SortedHeap<T>::deleteNodeByPos(const unsigned int pos){
    int last = this->heap.size() - 1;
    if(pos > last){
        return;
    }
    //与最后一个交换
    swap(this->heap[pos],this->heap[last]);
    //删除最后一个
    this->heap.pop_back();      

    this->adjustAfterDelete(pos);
}

template<typename T>
void SortedHeap<T>::deleteNode(int id){
    unsigned int pos;
    for(int i = 0; i < this->heap.size(); i++){
        if(heap[i].id == id){
            pos = i;
            break;
        }
    }
    this->deleteNodeByPos(pos);
    
}

template<typename T>
T SortedHeap<T>::popTopNode(){
    if(this->heap.size() != 0){
        T top = this->heap[0].obj;
        this->deleteNodeByPos(0);
        return top;
    }else{
        return T();
    }
}

template<typename T>
T SortedHeap<T>::getTopNode(){
    return this->heap[0].obj;
}

template<typename T>
void SortedHeap<T>::deleteTopNode(){
   if(this->heap.size() != 0){
        T top = this->heap[0].obj;
        this->deleteNodeByPos(0);
    }
}

#endif


