/**
 * filename:TimeoutException.h
 * socket超时异常类
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include <iostream>
#include <exception>

#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

class TimeoutException:public std::exception{
    public:
        const char * what (){
            return "timeout exception";
        }
        const char* getErrorCode(){
            return "E100001";
        }
};
#endif // !TIMEOUTEXCEPTION_H