#include "src/core/util/Timer.h"

bool Timer:: cmp(SchedulerEvent& a,SchedulerEvent& b) const{
    return a.deadline < b.deadline;
}

unsigned int Timer::setTimer(unsigned int interval,std::function<void()> action){
    SchedulerEvent event(interval,action);
    return this->eventQueue->insertNode(event);
}

void deleteTimer(unsigned int timerId){
    this->eventQueue->deleteNode(timerId);
}

void loopForExecute(){
    if(this->eventQueue->getTopNode().deadline <= this->timeline){
        //如果已经到了执行的时间
        event.action();
        //从堆中删除
        this->eventQueue->deleteTopNode();
    }
}

void start(std::chrono::milliseconds tick){
    
}