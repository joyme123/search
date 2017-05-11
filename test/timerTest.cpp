#include <iostream>
#include <chrono>
#include <string>
#include <functional>
#include <thread>

#include "src/core/util/Timer.h"

void myprint(std::string msg){
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "From Thread " << this_id << ":" << msg << std::endl;
}

int main(){
    std::chrono::milliseconds tick(1000);       //1000毫秒作为一个周期
    Timer timer(tick);
    std::function<void()> f1 = std::bind(myprint,"第一个加入");
    std::function<void()> f2 = std::bind(myprint,"第二个加入");
    std::function<void()> f3 = std::bind(myprint,"第三个加入");
    std::function<void()> f4 = std::bind(myprint,"第四个加入");

    timer.addEvent(10,f1);
    int id = timer.addEvent(11,f2);
    timer.addEvent(5,f3);
    timer.addEvent(20,f4);
    timer.deleteEvent(id);

    timer.start();  //定时器开始执行
}