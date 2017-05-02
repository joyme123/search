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
	return document;
}

Document DocumentParser::documentFormat(Package& package){
    Document document;
    document.title = package.title;
    document.url = package.url;
    document.type =package.type;
    /**************这中间的代码都需要分析******************/
    document.abstract = "测试文章摘要";
    document.author = "测试文章作者";
    document.wordNum = 10;

    std::cout << "DocumentParser->documentFormat(Package& package) 这里需要重写" << std::endl;

    return document;
}

Document DocumentParser:: documentJsonFormat(std::string& documentJson){
    auto dj = nlohmann::json::parse(documentJson);
    Document document;
    document.mongoId = dj.at("_id").get<std::string>();
    document.title = dj.at("title").get<std::string>();
    document.url = dj.at("url").get<std::string>();
    document.text = dj.at("content").get<std::string>();
    document.author = "测试作者";
    document.abstract = "测试摘要";
    document.type = html;

    std::cout << document.mongoId <<std::endl;
    return document;
}


