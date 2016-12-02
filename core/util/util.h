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
 * 计算一个utf-8编码的字符串的"字"的长度
 * @param str 要计算的字符串
 */
unsigned int getUtf8StringLength(std::string str);


/**
 * 传入一个char,根据utf8编码的特点判断这个char代表的字符长度(utf-8由1~4个char组成，可根据第一位char中开头1的个数判断具体长度)
 * @param c char
 */
unsigned int getUtf8CharLength(char c);

/**
 * 对中文和英文混合的字符串进行切割
 * @param str 要切割的字符串
 * @param start 切割的起点
 * @param end   切割的终点
 */
std::string substrWithChinese(std::string str,unsigned int start,unsigned int end);

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
 * 将两个char*数组合并为新的数组
 * @param first 第一个char数组指针
 * @param firstLen 第一个char数组长度
 * @param second 第二个char数组指针
 * @param secondLen 第二个char数组长度
 * @return 返回合并成的数组指针
 */
 char* mergeCharArray(char* first,unsigned int firstLen,char* second,unsigned int secondLen);

/**
 * 解析数据包专用,从char*中截取一段作为string,并将截取的最后位置剩下的信息返回
 *
 */
 std::string subCharArray(char*& cbuf,unsigned int& len,unsigned int start,int subLen);


#endif
