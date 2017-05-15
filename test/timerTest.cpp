#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <functional>
#include <thread>
#include <memory>
#include <fstream>
#include "src/core/util/Timer.h"

void myprint(std::string msg){
    std::ofstream of("timer.txt", std::ios::app);
    std::thread::id this_id = std::this_thread::get_id();
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    of << "From Thread " << this_id << "at time " << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << ":" << msg << std::endl;
}

int main(){
    std::chrono::milliseconds tick(2000);       //1000毫秒作为一个周期
    Timer* timer = Timer::getInstance(tick);
    std::function<void()> f1 = std::bind(myprint,"第一个加入,10tick后执行");
    std::function<void()> f2 = std::bind(myprint,"第二个加入，被删除不执行");
    std::function<void()> f3 = std::bind(myprint,"第三个加入，每5tick重复执行");
    std::function<void()> f4 = std::bind(myprint,"第四个加入，5tick后执行");
    std::function<void()> f5 = std::bind(myprint,"第五个加入，5tick后执行");
    std::function<void()> f6 = std::bind(myprint,"第六个加入，5tick后执行");
    std::function<void()> f7 = std::bind(myprint,"第七个加入，5tick后执行");
    std::function<void()> f8 = std::bind(myprint,"第八个加入，5tick后执行");
    std::function<void()> f9 = std::bind(myprint,"第九个加入，5tick后执行");
    std::function<void()> f10 = std::bind(myprint,"第十个加入，5tick后执行");
    std::function<void()> f11 = std::bind(myprint,"第十一个加入，15tick后执行");
    std::function<void()> f12 = std::bind(myprint,"第十二个在执行后加入，20tick+5s后执行");

    timer->addEvent(10,f1);
    int id = timer->addEvent(11,f2);
    timer->addEvent(5,f3,true);
    timer->addEvent(5,f4);
    timer->addEvent(5,f5);
    timer->addEvent(5,f6);   
    timer->addEvent(5,f7);
    timer->addEvent(5,f8);
    timer->addEvent(5,f9);
    timer->addEvent(5,f10);
    timer->addEvent(15,f11);

    timer->deleteEvent(id);

    myprint("线程开始启动,每tick是2秒");

    //异步执行，程序退出后计时器也会终止，因此在下面使用while循环保证程序不会退出
    timer->asyncStart();
    //timer->syncStart();


    //休眠5秒钟
    std::this_thread::sleep_for(std::chrono::seconds(5));   
    //应该在大概20*tick+5秒后执行,
    //TODO 执行后加入的定时器不对
    timer->addEvent(20,f12);

    getchar();

    return 0;
}