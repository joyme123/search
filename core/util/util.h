#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>
// #include<ctime>

std::wstring StringToWstring(const std::string str);

std::string WstringToString(const std::wstring str);

std::wstring getCurrentDateTimeStr();

#endif
