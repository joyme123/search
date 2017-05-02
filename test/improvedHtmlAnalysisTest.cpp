#include<iostream>
#include<string>
#include<fstream>
#include "src/core/analysis/DocumentAnalysis.h"
using namespace std;

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
    char* buffer=new char[size+1];

    // get file data
    pbuf->sgetn (buffer,size);

    buffer[size] = '\0';

    ifs.close();

    string str(buffer);

    DocumentAnalysis analysis;
    std::string content = analysis.improvedHtmlAnalysis(str);

    std::cout << content << std::endl;

    delete[] buffer;

    return 0;
}
