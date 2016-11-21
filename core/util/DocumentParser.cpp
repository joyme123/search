#include"DocumentParser.h"


wstring DocumentParser::peel(wstring html){

    return L" ";
}

vector<InvertedIndexHash> DocumentParser::parser(wstring text){
	
}

map< wstring, vector< int > > DocumentParser::ngram(wstring text,int step){
	map<wstring,vector<int> > map;
	int position = 1;
	wstring word = text.substr(0,1);
	for(int i = 0; text[i] != '\0'; i++){
		wstring word = text.substr(i,step);
		map[word].push_back(position);
		position++;
	}
	return map;
}

map< wstring, vector< int > > DocumentParser::splitWord(wstring text,friso_mode_t mode){
    friso_t friso;
    friso_config_t config;
    friso_task_t task;
    map< wstring, vector< int > > map;
    int pos = 1;
    //initialize
    friso = friso_new();
    config = friso_new_config();
    friso_set_mode(config,mode);
    if ( friso_init_from_ifile(friso, config, (fstring)FRISO_DICT_PATH) != 1 ) {
        //if initialize fail,free friso 
        printf("fail to initialize friso and config.");
        friso_free_config(config);
        friso_free(friso);
    }

    //set the task.
    task = friso_new_task();
    string str ;
    str = WstringToString(text);
    
    friso_set_text( task, (char*)str.c_str() );
    
    while ( ( config->next_token( friso, config, task ) ) != NULL ) 
    {
        wstring word = StringToWstring((string)task->token->word);
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
Document DocumentParser::documentFormat(wstring formatText)
{
    Document document;
    int count = 0;      //times of find |
    wstring title;
    DOCUMENT_TYPE type;
    wstring abstract;
    wstring author;
	wstring url;
    wstring text;
    wstring createTime;
    wstring updateTime;
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
	abstract = text.substr(0,text.length()/4 < 200 ? text.length()/4 : 200);
	document.title = title;
	document.abstract = abstract;
	document.author = author;
	document.type = type;
	document.url = url;
	document.text = text;
	document.createTime = getCurrentDateTimeStr();
	document.updateTime = getCurrentDateTimeStr();
	return document;
}


