/**
 * 定时器的实现
 * 支持int setTimer(T interval,function action):设置一个定时器，指定间隔interval和回调函数action,返回定时器id
 * 支持void deleteTimer(int timerId):删除一个定时器
 * 数据结构:最小堆模型，按照定时器触发的时间排序
 * author:jiangpengfei
 * date:2017-05-09
 */
#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>
#include <functional>

class Timer{
    private:
        struct heap_node{
            
        }
    public:
        /**
         * 设置定时器
         * @param interval 定时间隔
         * @param 
         */
        template<typename T>
        int setTimer(T interval,std::function<void()> action);
        void deleteTimer(int timerId);
};

#endif