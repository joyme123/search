/**
 * stripTags函数的单元测试
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//大写转成小写,小写则不动
char toLower(char c){
    if(c >= 65 && c <= 90){
        return c+32;
    }
    return c;
}

string stripTag(char* buf,size_t bufLen,char* allow,size_t allowLen){
    if(bufLen <= 0){
        return "";
    }
    char* copyBuf = (char*) malloc(sizeof(char) * (bufLen+1));
    memcpy(copyBuf,buf,bufLen);
    copyBuf[bufLen] = '\0';
    int bufIndex = 0;
    int copyBufIndex = 0;
    int state = 0;      //状态,0是正常状态,1是html，2是<!doctype><!-- -->不确定的状态,3是注释状态,4是script状态,5是style状态
    int i = 0;
    int br = 0;         //括号的计数
    int depth = 0;
    int inS = 0;
    char lc = '\0';     //上一个有意义的字符
    char c;
    while(i < bufLen){
        c = copyBuf[i];
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
                    case 4:
                        if(lc == 't'){
                            state = 0;
                            inS = 0;
                        }

                }
                lc = '>';
                break;

            case '?':
                goto reg_char;
                break;

            case 'T':
            case 't':
                if(state == 1 && lc == '<' && i > 5 && toLower(copyBuf[i - 1]) == 'p' && toLower(copyBuf[i - 2]) == 'i'
                    && toLower(copyBuf[i - 3]) == 'r' && toLower(copyBuf[i - 4]) == 'c' && toLower(copyBuf[i -5]) == 's'){
                        state = 4;
                        inS = 1;
                    }
                    else if(state == 4 && inS == 1 && lc != '\'' && i > 5 && toLower(copyBuf[i - 1]) == 'p' && toLower(copyBuf[i - 2]) == 'i'
                    && toLower(copyBuf[i - 3]) == 'r' && toLower(copyBuf[i - 4]) == 'c' && toLower(copyBuf[i -5]) == 's'){
                        lc = 't';
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
                if(state == 2 && i - copyBufIndex > 6 && toLower(copyBuf[i - 1]) == 'p' && toLower(copyBuf[i - 2]) == 'y'
                    && toLower(copyBuf[i - 3]) == 't' && toLower(copyBuf[i - 4]) == 'c' && toLower(copyBuf[i -5]) == 'o'
                    && toLower(copyBuf[i - 6]) == 'd'){
                        state = 1;
                    }
                break;

            case '-':
                if(state == 2&&copyBuf[i - 1] == '-'){
                    //注释
                    state = 3;
                }
                break;

            default:
reg_char:   
            if(state == 0)
                buf[bufIndex++] = c;    //有用的内容保存到buf中
        }
        i++;
    }
    free(copyBuf);
    buf[bufIndex] = '\0';
    return string(buf);
}

int main(int argc,char** argv){
    char* filepath;
    if(argc != 0){
         filepath = argv[1];
    }else{
        cout << "请输入分析html的本地路径" << endl;
        return 0;
    }

    std::ifstream ifs (filepath, std::ifstream::binary);

    // get pointer to associated buffer object
    std::filebuf* pbuf = ifs.rdbuf();

    // get file size using buffer's members
    std::size_t size = pbuf->pubseekoff (0,ifs.end,ifs.in);
    pbuf->pubseekpos (0,ifs.in);

    // allocate memory to contain file data
    char* buffer=new char[size];

    // get file data
    pbuf->sgetn (buffer,size);

    ifs.close();

    char* allow = (char*) malloc(sizeof(char) * 100);

    string res = stripTag(buffer,size,allow,100);
    
    cout << res << endl;
    ofstream outfile( "out_file.txt" );
    outfile << res;

    return 0;
}