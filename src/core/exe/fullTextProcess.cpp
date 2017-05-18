/**
 * 负责从数据库中查询文档进行处理
 * author:jiangpengfei12@gamil.com
 * date:2017-04-01
 */
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include "src/core/db/ResourceManage.h"
#include "src/core/controller/FullTextDocumentController.h"
#include "src/core/controller/WordController.h"
#include "src/core/util/util.h"

int main(){
    google::InitGoogleLogging("1");
    FullTextDocumentController controller;
    ResourceManage* manage = ResourceManage::getInstance();
    std::string documentJson;
    std::chrono::seconds time(5);       //5秒检查一次
    while(true){
        // std::ofstream outfile( "out_file.txt" );
        // outfile << documentJson;
        while((documentJson = manage->getNextDocument()) != ""){
            controller.documentEntry(documentJson);
        }

        std::this_thread::sleep_for(time);
    }

    std::cout << "所有文本已经索引完毕" << std::endl;
}