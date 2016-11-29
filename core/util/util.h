#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>
#include<cmath>
#include<ctime>
#include"config.h"

std::wstring StringToWstring(const std::string str);

std::string WstringToString(const std::wstring str);


/**
 * parse char vector to ingeter
 * @param v char vector
 * @return integer
 */
int VectorToInt(std::vector<char> v);

std::wstring getCurrentDateTimeStr();

DOCUMENT_TYPE getDocType(int type);

#endif
