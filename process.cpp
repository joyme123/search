/**
 * 负责从数据库中查询文档进行处理
 * author:jiangpengfei12@gamil.com
 * date:2017-04-01
 */
#include<iostream>
#include<fstream>
#include <string>
#include "core/DocumentController.h"
#include "core/WordController.h"
#include "core/util/ResourceManage.h"
#include "core/util/util.h"

int main(){
    google::InitGoogleLogging("1");
    DocumentController controller;
    ResourceManage* manage = ResourceManage::getInstance("127.0.0.1",6379,"127.0.0.1",27017);
    std::string documentJson;
    while((documentJson = manage->getNextDocument()) != "nil"){
        // std::ofstream outfile( "out_file.txt" );
        // outfile << documentJson;
        controller.documentJsonEntry(documentJson);
    }
}