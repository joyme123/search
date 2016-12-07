#include"DocumentAnalysis.h"

DocumentAnalysis::DocumentAnalysis(){
    this->k = 3;
    this->threshold = 20;
    blankChars.push_back('\t');
    blankChars.push_back('\r');
    blankChars.push_back('\v');
    blankChars.push_back('\f');
    blankChars.push_back('\n');
    blankChars.push_back(' ');
}

std::string DocumentAnalysis::htmlPeel(std::string html) const{
    std::regex reg("<\\s*script(\\s|\\S)*?<\\s*/script\\s*>|<\\s*style(\\s|\\S)*?<\\s*/style\\s*>|<!--(\\s|\\S)*?-->|<\\s*/{0,1}(\\s|\\S)*?>|&.*?;");                     //去除html标签的正则
    return this->htmlPeel(html,reg);
}

std::string DocumentAnalysis::htmlPeel(std::string html,std::regex regex) const{
    std::string formatedContent;
    //去除网页上的所有页面标签和css和script
    formatedContent = std::regex_replace(html,regex," ");
    return formatedContent;
}

/**
 * 去除<p>、<img>、<hx>、<td> 、<tr>、<th>或者等单独占用的行,将多行<br>或<br/>换成一行,将单个空<div></div>块的权重占行权重降为1,删除处理时间复杂度为O(n)
 */
std::string DocumentAnalysis::htmlFormat(std::string html) const{
    
    std::regex reg("\\s*</{0,1}(p|h\\d{1}|img).*?>\\s*|\\s*<\\s*br\\s*/\\s*>|\\s*<\\s*/{0,1}\\s*t(d|h|r)\\s*>\\s*|<div.*?>\\s*</div>");
    std::string formatedStr = std::regex_replace(html,reg," ");
    return formatedStr;
}

void DocumentAnalysis::setBlockLines(const int k){
    this->k = k;
}

void DocumentAnalysis::setThreshold(const int threshold){
    this->threshold = threshold;
}



std::string DocumentAnalysis::fastHtmlAnalysis(std::string html) const{
    int max = 0;           //存储最大的行块的值
    int maxPos;        //存储最大的行块的位置
    std::string content;        //存储最终的结果
    
    //去除网页上的所有页面标签和css和script
    std::string formatedContent = this->htmlPeel(html);

    if(formatedContent.length() < 20){
        return "test";
    }

    std::vector<std::string> lines;     //利用vector存储行

    std::string line;
    int i;
    for(i = 0; i < (int)formatedContent.length(); ++i){
        if(formatedContent[i] != '\n'){
            line.push_back(formatedContent[i]);
        }else{
            
            //遇到换行符
            lines.push_back(line);
            line.clear();
        }
    }
    lines.push_back(line);

    //lines分行结束，现在生成行块
    std::vector<std::string> blocks;


    for(i = 0; i < (int)lines.size() - k + 1; i++){
        std::string block;
        for(int j = 0; j < k; j++){
            block.append(lines[i+j]);
        }
        //删除block中的空白字符
        block = deleteCharArrayFromStr(block,blankChars);

        if((int)block.size() > max){
            max = block.size();
            maxPos = i;
        }
        blocks.push_back(block);
        block.clear();
    }

    

    //行块生成结束,因为记录了最大行块的位置，直接从最大行块向两边找即可
    int left;
    int right;
    for(left = maxPos - 1; (int)blocks[left].size() >= threshold && left >= 0;left--);        //找出骤起点
    left = left + 1;

    for(right = maxPos + 1; blocks[right].size() != 0 && right < (int)blocks.size();right++); //找出结束点
    right = right -1;


    for(i = left; i < right+k; i++){
        content.append(lines[i]);
    }

    return content;
}

std::string DocumentAnalysis::improvedHtmlAnalysis(std::string html) const{
    std::string formatedStr = this->htmlFormat(html);   //去除<p><hx><img>单独占行，将空<div></div>块占用权重降为1
    return this->fastHtmlAnalysis(formatedStr);
}