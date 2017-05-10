/**
 * 测试std::function作为回调函数的用法 
 * 和项目的代码无任何关系
 */

#include <iostream>
#include <functional>
#include <string>

using namespace std;

void callback(function<void()> fun){
    fun();
}


void echo(string text){
    cout << text << endl;
}

string multiEcho(string t1,string t2,string t3){
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;

    return t1+t2+t3;
}

int main(){

    //使用bind将参数"haha"绑定到echo方法
    function<void()> f = bind(&echo,"haha");
    callback(f);

    function<void()> mf = bind(&multiEcho,"Hello","world","haha");
    callback(mf);

}