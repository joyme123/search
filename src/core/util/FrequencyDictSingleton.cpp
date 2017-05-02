#include "FrequencyDictSingleton.h"

FrequencyDictSingleton* FrequencyDictSingleton::getInstance(){
    static FrequencyDictSingleton instance;
    return &instance;
}

FrequencyDictSingleton::FrequencyDictSingleton(){
    this->test = 10;
    std::cout << "执行单例模式的构造函数" << std::endl;
    //初始化频率map
    char* filepath = (char*)FREQUENCY_DICT_PATH;

    std::ifstream ifs (filepath, std::ifstream::in);
    if(!ifs){
        std::cout << "词频表文件不存在" <<std::endl;
        return;
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
}