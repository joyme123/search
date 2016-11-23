#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>
#include<cmath>
// #include<ctime>

std::wstring StringToWstring(const std::string str);

std::string WstringToString(const std::wstring str);

int VectorToInt(std::vector<char> v);

std::wstring getCurrentDateTimeStr();

#endif
