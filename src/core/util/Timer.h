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
#include "SortedHeap.hpp"

class Timer{
    private:
        struct SchedulerEvent{
          unsigned int id;          //定时事件的唯一标示id
          unsigned int deadline;    //定时事件的触发时间
          unsigned int timeline;    //当前时间线
          std::function<void()> action  //触发的事件
          SchedulerEvent(int deadline,std::function<void()> action){
              this->deadline = deadline;
              this->action = action;
          }
        };

        SortedHeap<SchedulerEvent> eventQueue;

        /**
         * 执行到达期限的定时器
         */
        void loopForExecute();

        /**
         * 启动定时器
         * @param tick 多少毫秒作为一个周期，这个周期越短，定时器精度越高，但是消耗也越多
         */
         void start(std::chrono::milliseconds tick);

    public:
        Timer():eventQueue(cmp){

        }

        /**
         * 定时事件的比较函数
         *
         */
        bool cmp(SchedulerEvent& a,SchedulerEvent& b) const;

        /**
         * 设置定时器
         * @param interval 定时间隔
         * @param action 定时执行的动作
         * @return unsigned int 定时器的id,可以根据这个id执行删除操作
         */
        unsigned int setTimer(unsigned int interval,std::function<void()> action);

        /**
         * 删除定时器
         * @param timerId 定时器id
         *
         */
        void deleteTimer(unsigned int timerId);

        
};


#endif