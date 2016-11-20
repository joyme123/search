#include <iostream>
#include "core/dao/DocumentDAO.h"
#include "core/dao/WordDAO.h"
#include "core/model/Document.h"

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
	Document document(L"测试标题",L"测试摘要",L"测试连接",L"测试作者",L"测试内容测试内容测试内容测试内容",100,L"2016-09-09 09:09:09",L"2016-09-09 09:09:09");
	DocumentDAO doc;
    int i=10000;
    int count = 0;
 	while(i--){
        doc.addDocument(document);
        count++;
    }
	cout << count << endl;
    return 0;
}
