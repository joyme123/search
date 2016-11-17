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

map< wstring, vector< int > > DocumentParser::splitWord(wstring text){

}

