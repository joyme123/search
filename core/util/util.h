#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cstring>
#include<string>
#include<clocale>
#include<cppconn/connection.h>
#include<cmath>
#include<ctime>
#include<vector>
#include"config.h"

std::wstring StringToWstring(const std::string str);

std::string WstringToString(const std::wstring str);

/**
 * 计算一个utf-8编码的字符串的"字"的长度
 * @param str 要计算的字符串
 */
int getUtf8StringLength(std::string str);


/**
 * 传入一个char,根据utf8编码的特点判断这个char代表的字符长度(utf-8由1~4个char组成，可根据第一位char中开头1的个数判断具体长度)
 * @param c char
 */
int getUtf8CharLength(char c);

/**
 * 对中文和英文混合的字符串进行切割
 * @param str 要切割的字符串
 * @param start 切割的起点
 * @param end   切割的终点
 */
std::string substrWithChinese(std::string str,int start,int end);

/**
 * parse char vector to ingeter
 * @param v char vector
 * @return integer
 */
int VectorToInt(std::vector<char> v);

/**
 * 获取当前时间
 */
std::string getCurrentDateTimeStr();


/**
 * 从字符串中删除指定字符，算法复杂度 O(n)
 * @param src 需要进行删除的源字符串,
 * @param charArray 被删除的字符集合
 * @param string 删除后生成的string
 */
 std::string deleteCharArrayFromStr(std::string src,std::vector<char> charArray);


/**
 * pair 的比较器
 * @return 比较结果
 */
 bool cmpByValue(const std::pair<std::string,std::vector<int> >& l, const std::pair<std::string,std::vector<int> >& r);
#endif
