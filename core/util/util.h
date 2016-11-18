#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>

using namespace std;

std::wstring StringToWstring(const std::string str);

std::string WstringToString(const std::wstring str);

#endif
