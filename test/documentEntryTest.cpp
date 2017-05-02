/**
 * filename: documentEntry.cpp
 * 接受原生文档，比如通过爬虫下载的未处理的网页
 * author:jiangpengfei
 * date: 2016-12-07
 */
#include <string>
#include "src/core/controller/HtmlDocumentController.h"
#include "src/core/controller/WordController.h"
#include "src/core/db/ResourceManage.h"
#include "src/core/util/util.h"


int main(int argc, char **argv) {
	google::InitGoogleLogging("1");

    HtmlDocumentController controller;
    ResourceManage* manage = ResourceManage::getInstance("127.0.0.1",6379,"127.0.0.1",27017);
    std::string documentJson;
    documentJson = manage->getNextDocument();
    controller.documentEntry(documentJson);
    return 0;
}
