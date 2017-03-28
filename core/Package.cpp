/**
 * filename:Package.cpp
 * Socket数据包
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#include "Package.h"

void Package::setBody(std::string body){
    int times = 0;      //\n的次数
    int len = 0;
    std::string tmp;
    auto it = body.begin();
    for(; it != body.end(); ++it){
        len++;
        if(*it == '\n'){
            if(times == 0)
                this->title = tmp;
            else if(times == 1){
                this->url = tmp;
            }else if(times == 2){
                this->type = DOCUMENT_TYPE::html;
                break;
            }
            *it++;
            times++;
            tmp.clear();
        }
        tmp.push_back(*it);
    }
    this->content = body.substr(len - 1,body.length() - len);

}