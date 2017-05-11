#include "src/core/util/Timer.h"

unsigned int Timer::addEvent(unsigned int interval,std::function<void()> action){
    SchedulerEvent event(interval,this->timeline,action);
    return this->eventQueue.insertNode(event);
}

void Timer::deleteEvent(unsigned int timerId){
    this->eventQueue.deleteNode(timerId);
}

void Timer::loopForExecute(){
    if(this->eventQueue.getTopNode().deadline <= this->timeline){
        //如果已经到了执行的时间,新开一个子线程执行任务
        std::thread t(this->eventQueue.getTopNode().action());
        t.detach();    //子线程分离
        //从堆中删除
        this->eventQueue.deleteTopNode();
    }
    //执行一次后等待一个周期
    std::this_thread::sleep_for(this->tick);
    //周期增1
    this->timeline++;
}

void Timer::start(){
    std::thread daemon_thread(Timer::loopForExecute);
    daemon_thread.detach();     //从当前主线程分离
}