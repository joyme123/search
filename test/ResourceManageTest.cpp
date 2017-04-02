/**
 * 测试ResourceManage的功能
 * author:jiang
 * date:2017-04-01
 */

 #include <iostream>
 #include "../core/util/ResourceManage.h"
 using namespace std;

 int main(){
     ResourceManage* manage = ResourceManage::getInstance("127.0.0.1",6379,"127.0.0.1",27017);
     cout << manage->getNextDocument() << endl;
 }