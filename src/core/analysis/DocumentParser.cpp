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


Document DocumentParser:: documentJsonFormat(std::string& documentJson){
    auto dj = nlohmann::json::parse(documentJson);
    Document document;
    document.mongoId = dj["_id"]["$oid"];
    document.title = dj.at("title").get<std::string>();
    document.url = dj.at("url").get<std::string>();
    document.text = dj.at("content").get<std::string>();
    document.author = "测试作者";
    document.abstract = "测试摘要";
    document.type = html;

    std::cout << document.mongoId <<std::endl;
    return document;
}


