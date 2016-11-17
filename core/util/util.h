#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>

using namespace std;

void printSqlError(sql::SQLException e){
    cout << "error happend:" << e.getErrorCode() <<" : " << e.what() << endl;
}

std::wstring StringToWstring(const std::string str)
{// string转wstring
    unsigned len = str.size() * 2;// 预留字节数
    setlocale(LC_CTYPE, "");     //必须调用此函数
    wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
    mbstowcs(p,str.c_str(),len);// 转换
    std::wstring str1(p);
    delete[] p;// 释放申请的内存
    return str1;
}

std::string WstringToString(const std::wstring str)
{// wstring转string
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char *p = new char[len];
    wcstombs(p,str.c_str(),len);
    std::string str1(p);
    delete[] p;
    return str1;
}

#endif
