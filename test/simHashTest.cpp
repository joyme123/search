/**
 * simHash函数的测试单元测试
 */

#include "../core/util/config.h"
#include "../core/util/SimHash.h"
#include "../core/util/DocumentAnalysis.h"
#include "../core/util/DocumentParser.h"
#include <iostream>
#include <map>
#include <string>
#include<vector>
#include<string>


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
    std::string content = analysis.improvedHtmlAnalysis(str);       //得到正文内容

    delete[] buffer;

    map<string,vector<int> > map =  DocumentParser::splitWord(content,__FRISO_COMPLEX_MODE__);         //得到正文的分词结果

    std::map<string,double> frequencyDict = initFrequencyDict();    //获取初始化的词频表
    std::map<string,int> stopWordDict = initStopWordDict();         //获取stopWord词汇表
    SimHash simHash;
    simHash.removeStopWord(map,stopWordDict);                       //移除stopWord
    std::bitset<SimHash::BITSET_LENGTH> bitset = simHash.calculate(map,frequencyDict);                           //计算特征码

    std::cout << bitset << std::endl;

    return 0;
}