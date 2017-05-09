/**
 * 排序堆的实现
 * 堆使用的是完全二叉树的结构，使用数组（数组从零开始）保存，那么最后一个非叶子节点为(n - 1) / 2
 * 堆的构建一直都是在有序的基础上的，那么每次调整只需比较i和(i - 1) / 2的元素，依次上推
 * 支持任意类的排序
 * author:jiangpengfie
 * date:2017-05-09
 */
#ifndef SORTEDHEAP_H
#define SORTEDHEAP_H
#include <iostream>
#include <vector>
#include <functional>
#include "src/core/util/util.h"


template<typename T>
class SortedHeap{
    private:
        std::vector<T> heap;
        std::function<void(T&,T&)> cmp;
        
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

        void swap(T& t1,T& t2);
    public:
        /**
         * 构造函数
         * @param cmp 用来比较
         */
        SortedHeap(std::function<void(T&,T&)> cmp);
        /**
         * 插入节点
         * @param node 插入的节点
         */
        int insertNode(T& node);
        /**
         * 删除节点
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
};
#endif