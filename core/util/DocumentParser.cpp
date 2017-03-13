#include"DocumentParser.h"

bool DocumentParser::htmlFileAnalysis(Document& document,std::string& content){
    return true;
}

bool DocumentParser::pdfFileAnalysis(Document& document,std::string& content){
    return true;
}

bool DocumentParser::wordFileAnalysis(Document& document,std::string& content){
    return true;
}


std::string DocumentParser::peel(std::string& html){

    return " ";
}

std::vector<InvertedIndexHash> DocumentParser::parser(std::string& text){
	std::vector<InvertedIndexHash> v;
	
	return v;
}

std::map< std::string, std::vector< int > > DocumentParser::ngram(std::string& text,int step){
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
std::map< std::string, std::vector< int > > DocumentParser::splitWord(std::string& text,friso_mode_t mode){
    friso_t friso;
    friso_config_t config;
    friso_task_t task;
    std::map<std:: string, std::vector< int > > map;
    int pos = 1;
    //initialize
    friso = friso_new();
    config = friso_new_config();
    friso_set_mode(config,mode);
    if ( friso_init_from_ifile(friso, config, (fstring)FRISO_DICT_PATH) != 1 ) {
        //if initialize fail,free friso 
        std::printf("fail to initialize friso and config.");
        friso_free_config(config);
        friso_free(friso);
		return map;
    }

    //set the task.
    task = friso_new_task();
    std::string str ;
    str = text;
    
    friso_set_text( task, (char*)str.c_str() );
    
    while ( ( config->next_token( friso, config, task ) ) != NULL ) 
    {
        std::string word = (std::string)task->token->word;
        map[word].push_back(pos++);
    }

    friso_free_task( task );

    return map;
}

/**
* input formated text and return a document object
* @param formatText formated text like this:title|type|author|url|text
* @return document
*/
Document DocumentParser::documentFormat(std::string& formatText){

    Document document;
    int count = 0;      //times of find |
    std::string title;
    DOCUMENT_TYPE type;
    std::string abstract;
    std::string author;
	std::string url;
    std::string text;
    std::string createTime;
    std::string updateTime;
    int pos = 0;
    int len = 0;
    for(int i = 0; formatText[i] != '\0'; i++){
        if(formatText[i] == '|'){
            count++;
            switch(count){
                case 1:
                    title = formatText.substr(pos,len);
                    break;
                case 2:
                    int cccnum;
                    cccnum = std::stoi(formatText.substr(pos,len),nullptr,0);
                    if(cccnum == 1){
                        type = html;
                    }else if(cccnum == 2){
                        type = pdf;
                    }else if(cccnum == 3){
                        type = word;
                    }
                    break;
                case 3:
                    author = formatText.substr(pos,len);
                    break;
				case 4:
					url = formatText.substr(pos,len);
            }
            pos = i+1;
            len=0;
        }else{
           len++; 
        }
    }
    text = formatText.substr(pos,len);
	
	//get title type author text,url,then generate abstract
    unsigned int textLen = getUtf8StringLength(text);
	abstract = substrWithChinese(text,0,textLen/4 < 200 ? textLen/4 : 200);
	document.title = title;
	document.abstract = abstract;
	document.author = author;
	document.type = type;
	document.url = url;
	document.text = text;
	document.createTime = getCurrentDateTimeStr();
    std::cout << "DocumentParser.cpp 143行：当前文档设定的时间为" << document.createTime << std::endl;
	document.updateTime = getCurrentDateTimeStr();
	return document;
}

Document DocumentParser::documentFormat(Package& package){
    Document document;
    document.url = package.url;
    document.type =package.type;
    document.text = package.content;
    /**************这中间的代码都需要分析******************/

    document.title = "测试标题";
    document.abstract = "测试文章摘要";
    document.author = "测试文章作者";
    document.wordNum = 10;

    std::cout << "DocumentParser->documentFormat(Package& package) 这里需要重写" << std::endl;

    /**************************************************/
    document.createTime = getCurrentDateTimeStr();
    std::cout << "DocumentParser.cpp 143行：当前文档设定的时间为" << document.createTime << std::endl;
	document.updateTime = getCurrentDateTimeStr();
    return document;
}


