/**
 * 负责从数据库中查询文档进行处理
 * author:jiangpengfei12@gamil.com
 * date:2017-04-01
 */
#include <iostream>
#include <fstream>
#include <string>
#include "src/core/db/ResourceManage.h"
#include "src/core/controller/HtmlDocumentController.h"
#include "src/core/controller/WordController.h"
#include "src/core/util/util.h"

int main(){
    google::InitGoogleLogging("1");
    HtmlDocumentController controller;
    ResourceManage* manage = ResourceManage::getInstance();
    std::string documentJson;
    while((documentJson = manage->getNextDocument()) != ""){
        // std::ofstream outfile( "out_file.txt" );
        // outfile << documentJson;
        controller.documentEntry(documentJson);
    }

    std::cout << "所有文本已经索引完毕" << std::endl;
}