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
    std::chrono::milliseconds tick(1000);       //1000毫秒作为一个周期
    Timer* timer = Timer::getInstance(tick);
    std::function<void()> f1 = std::bind(myprint,"第一个加入,10s后执行");
    std::function<void()> f2 = std::bind(myprint,"第二个加入，被删除不执行");
    std::function<void()> f3 = std::bind(myprint,"第三个加入，5s后执行");
    std::function<void()> f4 = std::bind(myprint,"第四个加入，5s后执行");
    std::function<void()> f5 = std::bind(myprint,"第五个加入，5s后执行");
    std::function<void()> f6 = std::bind(myprint,"第六个加入，5s后执行");
    std::function<void()> f7 = std::bind(myprint,"第七个加入，5s后执行");
    std::function<void()> f8 = std::bind(myprint,"第八个加入，5s后执行");
    std::function<void()> f9 = std::bind(myprint,"第九个加入，5s后执行");
    std::function<void()> f10 = std::bind(myprint,"第十个加入，15s后执行");
    std::function<void()> f11 = std::bind(myprint,"第十一个在执行后加入，25s后执行");

    timer->addEvent(10,f1);
    int id = timer->addEvent(11,f2);
    timer->addEvent(5,f3);
    timer->addEvent(5,f4);
    timer->addEvent(5,f5);
    timer->addEvent(5,f6);   
    timer->addEvent(5,f7);
    timer->addEvent(5,f8);
    timer->addEvent(5,f9);
    timer->addEvent(15,f10);

    timer->deleteEvent(id);

    //异步执行，程序退出后计时器也会终止，因此在下面使用while循环保证程序不会退出
    timer->asyncStart();

    //休眠5秒钟
    std::this_thread::sleep_for(std::chrono::seconds(5));   
    //应该在大概25秒后执行
    timer->addEvent(20,f11);

    while(1){}

    return 0;
}

//同步执行的结果
// From Thread 140597152700160at time 2017-05-12 15.32.10:第九个加入，5s后执行
// From Thread 140597135914752at time 2017-05-12 15.32.10:第七个加入，5s后执行
// From Thread 140597127522048at time 2017-05-12 15.32.10:第六个加入，5s后执行
// From Thread 140597144307456at time 2017-05-12 15.32.10:第四个加入，5s后执行
// From Thread 140597119129344at time 2017-05-12 15.32.10:第五个加入，5s后执行
// From Thread 140597110736640at time 2017-05-12 15.32.10:第八个加入，5s后执行
// From Thread 140597161092864at time 2017-05-12 15.32.10:第三个加入，5s后执行
// From Thread 140597161092864at time 2017-05-12 15.32.15:第一个加入,10s后执行
// From Thread 140597161092864at time 2017-05-12 15.32.20:第十个加入，15s后执行

//异步执行的结果
// From Thread 139836863350528at time 2017-05-12 15.42.15:第四个加入，5s后执行
// From Thread 139836871743232at time 2017-05-12 15.42.15:第三个加入，5s后执行
// From Thread 139836846565120at time 2017-05-12 15.42.15:第六个加入，5s后执行
// From Thread 139836838172416at time 2017-05-12 15.42.15:第七个加入，5s后执行
// From Thread 139836854957824at time 2017-05-12 15.42.15:第九个加入，5s后执行
// From Thread 139836863350528at time 2017-05-12 15.42.20:第八个加入，5s后执行
// From Thread 139836838172416at time 2017-05-12 15.42.20:第五个加入，5s后执行
// From Thread 139836854957824at time 2017-05-12 15.42.20:第一个加入,10s后执行
// From Thread 139836863350528at time 2017-05-12 15.42.25:第十个加入，15s后执行
// From Thread 139836863350528at time 2017-05-12 15.42.34:第十一个在执行后加入，25s后执行