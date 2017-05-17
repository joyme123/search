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

std::string DocumentAnalysis::htmlPeel(std::string& html) const{
    ////去除html标签<script><style><!-- -->< />的正则和&nbsp;
    //std::regex reg("<\\s*script(\\s|\\S)*?<\\s*/script\\s*>|<\\s*style(\\s|\\S)*?<\\s*/style\\s*>|<!--(\\s|\\S)*?-->|<\\s*/{0,1}(\\s|\\S)*?>|\\s*&.*?;\\s*");                     
    char* cs = "";
    std::string peeledString = stripTags(html.c_str(),html.length(),cs,0);

    //std::cout << "去除标签后的文本为:"+formatedStr << std::endl;
    return peeledString;
}


/**
 * 去除<p>、<img>、<hx>、<td> 、<tr>、<th>或者等单独占用的行,将多行<br>或<br/>换成一行,将单个空<div></div>块的权重占行权重降为1,删除处理时间复杂度为O(n)
 */
std::string DocumentAnalysis::htmlFormat(std::string& html) const{
    
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



std::string DocumentAnalysis::fastHtmlAnalysis(std::string& peeledHtml) const{
    int max = 0;           //存储最大的行块的值
    int maxPos = 0;        //存储最大的行块的位置
    std::string content;        //存储最终的结果

    if(peeledHtml.length() < 20){
        return "test";
    }

    std::vector<std::string> lines;     //利用vector存储行

    std::string line;
    int i;
    for(i = 0; i < (int)peeledHtml.length(); ++i){
        if(peeledHtml[i] != '\n'){
            line.push_back(peeledHtml[i]);
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

    
    if(blocks.size() >= 3){

        //行块生成结束,因为记录了最大行块的位置，直接从最大行块向两边找即可
        int left = maxPos;
        
        if(left >= 0){
            for(;left >= 0 &&(int)blocks[left].size() >= threshold  ;left--);        //找出骤起点
            left = left + 1;
        }

        int right = maxPos;
        for( ;right < (int)blocks.size()&&blocks[right].size() != 0;right++); //找出结束点
        right = right -1;


        for(i = left; i < right+k; i++){
            if((int)lines.size() > i)
                content.append(lines[i]);
        }
    }else{
        content = peeledHtml;
    }

    return content;
}

std::string DocumentAnalysis::improvedHtmlAnalysis(std::string& html) const{
    std::string formatedHtml = this->htmlFormat(html);      //去除<p><hx><img>单独占行，将空<div></div>块占用权重降为1

    std::string peeledHtml = this->htmlPeel(formatedHtml);  //统一去除所有的标签

    return this->fastHtmlAnalysis(peeledHtml);              //提取出网页正文
}