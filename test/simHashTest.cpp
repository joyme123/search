/**
 * simHash函数的单元测试
 */

#include "../core/util/config.h"
#include "../core/util/SimHashCal.h"
#include "../core/util/DocumentAnalysis.h"
#include "../core/util/DocumentParser.h"
#include "../core/util/FrequencyDictSingleton.h"
#include "../core/util/StopWordDictSingleton.h"
#include "../core/util/WordSplitSingleton.h"
#include <iostream>
#include <map>
#include <string>
#include<vector>
#include<string>


using namespace std;

//全局初始化的变量
//std::map<std::string,double> frequencyDict = initFrequencyDict();          //获取初始化的词频表
//std::map<std::string,int> stopWordDict = initStopWordDict();               //获取stopWord词汇表

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

    
    FrequencyDictSingleton *frequencyDictInstance = FrequencyDictSingleton::getInstance();      //获取词频表的单例
    //测试单例模式的构造函数没有被重复执行
    FrequencyDictSingleton *frequencyDictInstance1 = FrequencyDictSingleton::getInstance();      //获取词频表的单例
    StopWordDictSingleton *stopWordDictInstance = StopWordDictSingleton::getInstance();         //获取停顿词的单例
    WordSplitSingleton *wordSpilt = WordSplitSingleton::getInstance(__FRISO_COMPLEX_MODE__);

    DocumentAnalysis analysis;
    std::string content = analysis.improvedHtmlAnalysis(str);       //得到正文内容

    std::cout << "正文是:" << content << std::endl;

    delete[] buffer;

    map<string,vector<int> > resultMap =  wordSpilt->splitWord(content);         //得到正文的分词结果

    SimHashCal simHashCal;
    map<string,vector<int> > removedResultMap = simHashCal.removeStopWord(resultMap,stopWordDictInstance->stopWordDict);    //移除stopWord   

    std::bitset<SimHashCal::BITSET_LENGTH> bitset = simHashCal.calculate(removedResultMap,frequencyDictInstance->frequencyDict);                           //计算特征码

    std::cout << bitset << std::endl;

    return 0;
}