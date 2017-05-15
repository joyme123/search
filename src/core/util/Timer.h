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
#include <thread>
#include <memory>
#include "SortedHeap.hpp"

class Timer{
    private:
        std::chrono::milliseconds tick;
        double timeline;     //当前时间线,long double的字节数为12
        bool isStart;        //标志当前定时器的启动状态
        struct SchedulerEvent{
          unsigned int id;                   //定时事件的唯一标示id
          double interval;                   //事件的触发间隔，在重复事件中会用到这个属性
          double deadline;                   //定时事件的触发时间
          std::function<void()> action;      //触发的事件
          bool isRepeat;                     //是否是重复执行事件
          SchedulerEvent( double interval, double timeline,std::function<void()> action,bool isRepeat){
              this->interval = interval;
              this->deadline = interval + timeline;
              this->action = action;
              this->isRepeat = isRepeat;
          }
        };

        SortedHeap<SchedulerEvent> eventQueue;

        /**
         * 执行到达期限的定时器
         */
        void loopForExecute();

        //私有的构造函数
        Timer(std::chrono::milliseconds tick):eventQueue(
            [](SchedulerEvent& a,SchedulerEvent& b){
                return a.deadline < b.deadline;
            }
        ){
            this->timeline = 0;
            this->tick = tick;
            this->isStart = false;
        }

    public:
        
        //单例模式
        static Timer* getInstance(std::chrono::milliseconds tick){
            static Timer timer(tick);
            return &timer;
        }

        /**
         * 设置定时器
         * @param interval 定时间隔
         * @param action 定时执行的动作
         * @param isRepeat 是否重复执行,默认不重复执行
         * @return unsigned int 定时器的id,可以根据这个id执行删除操作
         */
        unsigned int addEvent(double interval,std::function<void()> action,bool isRepeat = false);

        /**
         * 删除定时器
         * @param timerId 定时器id
         *
         */
        void deleteEvent(unsigned int timerId);

        /**
         * 同步执行启动定时器
         */
         void syncStart();

         /**
         * 异步执行启动定时器
         */
         void asyncStart();
        
};


#endif