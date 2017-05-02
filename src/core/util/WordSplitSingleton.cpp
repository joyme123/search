#include "WordSplitSingleton.h"

/**
* 使用ngram算法进行文本的分词
* @param text 文本内容
* @param step 分词步长
* @return map key为单词，value保存单词出现的位置
*/
std::map< std::string, std::vector< int > > WordSplitSingleton::ngram(std::string& text,int step){
	std::map<std::string,std::vector<int> > map;
	int position = 1;
	std::string word = text.substr(0,1);
	for(int i = 0; text[i] != '\0'; i++){
		std::string word = text.substr(i,step);
		map[word].push_back(position);
		position++;
	}
	return map;
}


/**
 * 基于friso的分词函数
 * @param text 文本内容
 * @param mode friso支持的分词模式
 * @return map key为单词，value保存单词出现的位置
 */
std::map< std::string, std::vector< int > > WordSplitSingleton::splitWord(std::string& text){

    std::map<std:: string, std::vector< int > > map;
    int pos = 1;
    friso_task_t task;

    //set the task.
    task = friso_new_task();
    
    friso_set_text( task, (char*)text.c_str() );
    
    while ( ( this->config->next_token( this->friso, this->config, task ) ) != NULL ) 
    {
        std::string word = (std::string)task->token->word;
        map[word].push_back(pos++);
    }

    friso_free_task( task );
    return map;
}

WordSplitSingleton* WordSplitSingleton::getInstance(friso_mode_t mode){
    static WordSplitSingleton instance(mode);
    return &instance;
}

WordSplitSingleton::WordSplitSingleton(friso_mode_t mode){
    //initialize
    this->friso = friso_new();
    this->config = friso_new_config();
    friso_set_mode(config,mode);
    ConfigReader* reader =  ConfigReader::getInstance();
    std::string pathStr = reader->get("friso_dict_path");
    const char* filepath = pathStr.c_str();

    if ( friso_init_from_ifile(friso, config, (fstring)filepath) != 1 ) {
        //if initialize fail,free friso 
        std::printf("fail to initialize friso and config.");
    }
}

WordSplitSingleton::~WordSplitSingleton(){
    friso_free_config(this->config);
    friso_free(this->friso);
}