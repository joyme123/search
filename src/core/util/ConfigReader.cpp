#include"ConfigReader.h"

void ConfigReader::open(const char * path){
    std::ifstream ifs (path, std::ifstream::binary);

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
    std::string strLine;       //代表每一行的文本
    std::string str(buffer);//获取到配置文件中的全部文本内容
    


}

std::string ConfigReader::get(std::string key){

}