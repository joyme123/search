#include"config.h"

std::map<std::string,double>  initFrequencyDict(){
    std::map<std::string,double> frequencyDict;
    //初始化频率map
    char* filepath = (char*)FREQUENCY_DICT_PATH;



    std::ifstream ifs (filepath, std::ifstream::in);
    if(!ifs){
        std::cout << "词频表文件不存在" <<std::endl;
        return frequencyDict;
    }
    char line[40];
    
    while(ifs.getline(line,40)){
        char dbl[10];
        char word[30];
        int i,j;        //计数器
        for(i = 0; line[i] != '|'; i++){
            dbl[i] = line[i];
        }
        dbl[i] = '\0';
        for(j = i + 1; line[j] != '\0'; j++){
            word[j - i -1] = line[j];
        }
        word[j] = '\0';
        std::string wordstr(word);
        std::string dbstr(dbl);
        double f = std::stod(dbstr);
        frequencyDict[wordstr] = f;
    }
    ifs.close();

    return frequencyDict;
}

std::map<std::string,int>  initStopWordDict(){
    std::map<std::string,int> stopWordDict;

    //初始化频率map
    char* filepath = (char*)STOPWORD_CN_DICT_PATH;



    std::ifstream ifs (filepath, std::ifstream::in);
    if(!ifs){
        std::cout << "stopword文件不存在" <<std::endl;
        return stopWordDict;
    }
    char line[40];
    
    while(ifs.getline(line,40)){
        std::string stopWordStr(line);
        stopWordDict[stopWordStr] = 1;
    }
    ifs.close();
    
    return stopWordDict;
}