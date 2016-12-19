#include"StopWordDictSingleton.h"

StopWordDictSingleton* StopWordDictSingleton::getInstance(){
    static StopWordDictSingleton instance;
    return &instance;
}

StopWordDictSingleton::StopWordDictSingleton(){
    this->test = 10;
    //初始化stopword map
    char* filepath = (char*)STOPWORD_DICT_PATH;



    std::ifstream ifs (filepath, std::ifstream::in);
    if(!ifs){
        std::cout << "stopword文件不存在" <<std::endl;
        return;
    }
    char line[40];
    
    while(ifs.getline(line,40)){
        std::string stopWordStr(line);
        stopWordDict[stopWordStr] = 1;
    }
    ifs.close();
}