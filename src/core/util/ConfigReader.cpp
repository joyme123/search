#include"ConfigReader.h"

ConfigReader* ConfigReader::getInstance(){
    static ConfigReader reader("/etc/search/s.conf");
    return &reader;
}

ConfigReader* ConfigReader::getInstance(const char* path){
    static ConfigReader reader(path);
    return &reader;
}

void ConfigReader::open(){
    std::ifstream ifs (path, std::ifstream::binary);

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
    std::string key = "";       //代表键
    std::string value = "";     //代表值
    bool isKey = true;          //当前读取的是key还是value    
    char lastChar = '\0';       //代表行首
    for(std::size_t i = 0; i < size; i++){
        if(buffer[i] != '\n'){
            //没有换行

            if(lastChar == '\0' && buffer[i] == '#'){
                //在行首遇到了#号，则表明这是注释，跳过这一行
                while(buffer[++i] != '\n' && i < size + 1);
                continue;   
            }
            
            if(buffer[i] != ' '){
                //如果当前不是空格
                if(isKey){
                    key.push_back(buffer[i]);
                }else{
                    value.push_back(buffer[i]);
                }
                
            }else if((lastChar != '\0' && lastChar != ' ') && buffer[i] == ' '){
                //如果不处于行首并且上一个不是空格,此时遇到了空格，表明处于value处
                isKey = false;
            }
            lastChar = buffer[i];
            
        }else{
            //到了换行,如果key和value都有值
            if(key != "" && value != ""){
                this->config[key] = value;
            }
            key = "";
            value = "";
            lastChar = '\0';
            isKey = true;
        }
    }

    //文件结尾还有key和value
    if(key != "" && value != ""){
        this->config[key] = value;
    }
}

std::string ConfigReader::get(std::string key){
    std::string value;
    auto search = this->config.find(key);
    if(search != this->config.end()){
       value = search->second;
    }else{
        value = "";
        LOG(ERROR) << "ConfigReader->get(std::string key):不存在该值";
    }
    return value;
}