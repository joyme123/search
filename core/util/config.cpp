#include"config.h"

static std::map<std::string,double>  initFrequencyDict(){
	if(!frequencyInit){
        //初始化频率map
        char* filepath = FREQUENCY_DICT_PATH;

        std::ifstream ifs (filepath, std::ifstream::in);
        std::string line = ifs.getline();
        while(ifs.good()){
            char dbl[10];
            char word[30];
            for(int i = 0; line[i] != '|'; i++){
                dbl[i] = line[i];
            }
            dbl[i] = '\0'
            for(int j = i + 1; line[j] != '\0'; j++){
                word[j - i -1] = line[j];
            }
            word[j] = '\0';
            std::string wordstr(word);
            std::string dbstr(dbl);
            double f = std::stod(dbstr);
            frequency[wordstr] = f;
        }
        ifs.close();
        frequencyInit = true;
	}

    return frequencyInit;
}