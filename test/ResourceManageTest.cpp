/**
 * 测试ResourceManage的功能
 * author:jiang
 * date:2017-04-01
 */

 #include <iostream>
 #include "src/core/db/ResourceManage.h"
 using namespace std;

 int main(){
     ResourceManage* manage = ResourceManage::getInstance();
     cout << manage->getNextDocument() << endl;
 }