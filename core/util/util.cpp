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



unsigned int getUtf8StringLength(std::string str){
    unsigned int i = 0;
    unsigned int cursor = 0;
    while(str[i] != '\0'){
        unsigned int l = getUtf8CharLength(str[i]); //获取字符长度
        i+=l;
        cursor++;
    }
    return cursor;
}

unsigned int getUtf8CharLength(char c){
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

std::string substrWithChinese(std::string str,unsigned int start,unsigned int length){
    unsigned int i = 0;
    unsigned int cursor = 0;
    unsigned int save = 0;
    unsigned int len = str.length();
    char* c = new char[len + 1];
    while(str[i] != '\0'&&length > 0){
        unsigned int l = getUtf8CharLength(str[i]); //获取字符长度
        if(cursor >= start){
            unsigned int m = l;
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
