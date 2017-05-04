#include"util.h"
#include<bitset>

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

int VectorToInt(std::vector<char> v){
    int len = v.size();
    int res = 0;
    for(int i = 0; i < len; i++){
        res = res + (v[i] - '0')*pow(10,len-i-1);
    }
    return res;
}


std::string getCurrentDateTimeStr()
{
	time_t now = std::time(0);
    tm *ltm = std::localtime(&now);
    std::string datetime;
    datetime = std::to_string(1900+ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + " " +std::to_string(ltm->tm_hour) + ":" + std::to_string(1 + ltm->tm_min) + ":" + std::to_string(1 + ltm->tm_sec);
	return datetime;
}


int getUtf8StringLength(std::string str){
    int i = 0;
    int cursor = 0;
    while(str[i] != '\0'){
        int l = getUtf8CharLength(str[i]); //获取字符长度
        i+=l;
        cursor++;
    }
    return cursor;
}

int getUtf8CharLength(char c){
    int len = 0;
    if(c > 0){
        return len + 1;     //第一位为0时为特殊情况，需要加1
    }
    while(c < 0){
        len++;
        c = c << 1;
    }
    return len;
}

std::string substrWithChinese(std::string str,int start,int length){
    int i = 0;
    int cursor = 0;
    int save = 0;
    int len = str.length();
    char* c = new char[len + 1];
    while(str[i] != '\0'&&length > 0){
        int l = getUtf8CharLength(str[i]); //获取字符长度
        if(cursor >= start){
            int m = l;
            while(m--){
                c[save++] = str[i++];
            }
            length--;
        }else{
            i+=l;
        }
        cursor++;
    }
    c[i] = '\0';
    return std::string(c);
}

 std::string deleteCharArrayFromStr(std::string src,std::vector<char> charArray){
     //先用charset生成map
     std::map<char,int> charMap;
     for(unsigned int i = 0; i < charArray.size(); i++){
         charMap[charArray[i]] = 1;
     }

     int fastPos = 0,slowPos = 0;    //分别指向string中的两个位置

     while(fastPos < (int)src.size()){
        if(charMap[src[fastPos]] != 1){
            //不需要删除
            src[slowPos] = src[fastPos];
            slowPos++;
        }

        fastPos++;
     }
     src[slowPos] = '\0';
     std::string tmp(src.c_str());
     return tmp;
 }
 bool cmpByValue(const std::pair<std::string,std::vector<int> >& l, const std::pair<std::string,std::vector<int> >& r){
     return l.second.size() > r.second.size();
 }

bool cmpMapByValue(const std::pair<int,int>& l,const std::pair<int,int>& r){
    return l.second > r.second;
}


char toLower(char c){
    if(c >= 65 && c <= 90){
        return c+32;
    }
    return c;
}

std::string stripTags(const char* buf,size_t bufLen,char* allow,size_t allowLen){
    if(bufLen <= 0){
        return "";
    }
    char* bufTmp = (char*) malloc(sizeof(char) * (bufLen+1));
    int bufIndex = 0;
    int copyBufIndex = 0;
    int state = 0;      //状态,0是正常状态,1是html，2是<!doctype><!-- -->不确定的状态,3是注释状态,4是script状态,5是style状态
    int i = 0;
    int depth = 0;
    int inS = 0;
    char lc = '\0';     //上一个有意义的字符
    char c;
    while(i < bufLen){
        c = buf[i];
        switch(c){
            case '\0':
                break;
            case '<':
                if(state == 0){
                    state = 1;
                }else if(state == 1){
                    depth++;
                }
                if(inS == 0)
                    lc = '<';
                
                break;
            case '>':
                switch(state){
                    case 1:
                        //html中
                        if(depth > 0){
                            //还没到结尾
                            depth--;
                        }else{
                            //到结尾了
                            state = 0;  //回到正常状态
                        }
                        break;
                    case 3:
                        if(lc == '<')
                            state = 0;
                        break;
                    case 4:
                        if(lc == 't'){
                            state = 0;
                            inS = 0;
                        }
                    case 5:
                        if(lc == 'e'){
                            state = 0;
                            inS = 0;
                        }
                        break;
                    default:
                        goto reg_char;

                }
                lc = '>';
                break;

            case '?':
                goto reg_char;
                break;

            case 'T':
            case 't':
                if(state == 1 && lc == '<' && i > 5 && toLower(buf[i - 1]) == 'p' && toLower(buf[i - 2]) == 'i'
                    && toLower(buf[i - 3]) == 'r' && toLower(buf[i - 4]) == 'c' && toLower(buf[i -5]) == 's'){
                    state = 4;
                    inS = 1;
                }
                else if(state == 4 && inS == 1 && lc != '\'' && i > 5 && toLower(buf[i - 1]) == 'p' && toLower(buf[i - 2]) == 'i'
                && toLower(buf[i - 3]) == 'r' && toLower(buf[i - 4]) == 'c' && toLower(buf[i -5]) == 's'&& toLower(buf[i -6]) == '/'&& toLower(buf[i -7]) != '\\'){
                    lc = 't';
                }else{
                    //不是特殊字符则跳到reg_char
                    goto reg_char;
                }
                break;

            case '\"':
            case '\'':
                if(inS == 0 || (inS == 1 && lc != '>'))
                    lc = '\'';
                break;


            case 'l':
            case 'L':
                goto reg_char;
                break;

            case '!':
                if(state == 1){
                    state = 2;
                }else{
                    goto reg_char;
                }
                break;

            case 'e':
            case 'E':
                if(state == 2 && i - copyBufIndex > 6 && toLower(buf[i - 1]) == 'p' && toLower(buf[i - 2]) == 'y'
                    && toLower(buf[i - 3]) == 't' && toLower(buf[i - 4]) == 'c' && toLower(buf[i -5]) == 'o'
                    && toLower(buf[i - 6]) == 'd'){
                        state = 1;
                    }else if(state == 1 && lc == '<' && i > 5 && toLower(buf[i - 1]) == 'l' && toLower(buf[i - 2]) == 'y'
                    && toLower(buf[i - 3]) == 't' && toLower(buf[i - 4]) == 's'){
                        state = 5;
                        inS = 1;
                    }else if(state == 5 && inS == 1 && lc != '\'' && i > 5 && toLower(buf[i - 1]) == 'l' && toLower(buf[i - 2]) == 'y'
                && toLower(buf[i - 3]) == 't' && toLower(buf[i - 4]) == 's' && toLower(buf[i -5]) == '/'&& toLower(buf[i -6]) != '\\'){
                        lc = 'e';
                    }else{
                        //不是特殊字符则跳到reg_char
                        goto reg_char;
                    }
                break;

            case '-':
                if(state == 2&&buf[i - 1] == '-'){
                    //注释
                    state = 3;
                }else{
                    //不是特殊字符则跳到reg_char
                    goto reg_char;
                }
                break;

            default:
reg_char:   
            if(state == 0)
                bufTmp[bufIndex++] = c;    //有用的内容保存到buf中
        }
        i++;
    }
    bufTmp[bufIndex] = '\0';
    std::string s = std::string(bufTmp);
    free(bufTmp);
    return s;
}
