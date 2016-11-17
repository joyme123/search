#include"DocumentParser.h"

wstring DocumentParser::peel(wstring html){

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

