#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <functional>
#include <thread>
#include <memory>
#include "src/core/util/Timer.h"
#include "src/core/util/Trie.h"
#include "src/include/json.hpp"
using namespace std;
using json = nlohmann::json;

json formatKeywordToJson(std::vector<Keyword> suggesstions){
	json j;
	for(unsigned int i = 0; i < suggesstions.size(); i++){
		json tmp;
		Keyword keyword = suggesstions[i];
		tmp["suggestion"] = WstringToString(keyword.word);
		tmp["count"] = keyword.count;
		j.push_back(tmp);
	}
    cout << j.dump(4) << endl;
	return j;
}

void myprint(std::string msg){
    std::ofstream of("timer_a.txt", std::ios::app);
    std::thread::id this_id = std::this_thread::get_id();
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    of << "From Thread " << this_id << "at time " << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << ":" << msg << std::endl;
}

void fun(){
    
    locale loc("zh_CN.UTF-8");
    locale::global(loc);
    Trie trie;
    std::string path = "/home/jiang/search-data/suggestion/source.txt";
    std::string save_path = "/home/jiang/search-data/suggestion/";
    trie.read(path);

	
	std::chrono::milliseconds tick(1000);       //1秒作为一个周期
    Timer* timer = Timer::getInstance(tick);
	std::function<void()> f1 = std::bind(&Trie::persist,&trie,std::ref(save_path));
	std::function<void()> f2 = std::bind(myprint,"第二个加入");
	timer->addEvent(6,f1,true);		//6个周期，也就是6秒钟保存一次
	timer->addEvent(6,f2,true);	

	timer->asyncStart();  


    wstring word;
    cout << "输入exit退出程序" << endl;
    while(wcin >> word){
        if(word == L"exit"){
            break;
        }
        std::vector<Keyword> keywords =  trie.searchPrefix(word);   //搜索
        trie.addWordToTrie(word);                                   //添加到树中
        formatKeywordToJson(keywords);
    }

}

int main(){
    fun();
    return 1;
}