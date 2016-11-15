#include"DocumentParser.h"

string DocumentParser::peel(string html){

}

vector<InvertedIndexHash> DocumentParser::parser(string text){
	
}

map< string, vector< int > > DocumentParser::ngram(string text,int step){
	map<string,vector<int> > map;
	int position = 1;
	for(int i = 0; string[i] != '\0'; i+=step){
		string word = text.substr(i,i+step-1);
		map[word].push_back(position);
		position++;
	}
}

map< string, vector< int > > DocumentParser::splitWord(string text){

}

