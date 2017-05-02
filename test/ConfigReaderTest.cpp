#include "src/core/util/ConfigReader.h"

int main(){
    //const char* path = "/etc/search/s.conf";
    ConfigReader* reader = ConfigReader::getInstance();
    std::cout << reader->get("friso_dict_path") << "|" << std::endl;
    std::cout << reader->get("stopword_dict_path") << "|" << std::endl;
    std::cout << reader->get("freq_dict_path") << "|" << std::endl;
}