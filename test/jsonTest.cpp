#include "../include/json.hpp"

using json = nlohmann::json;

int main(){
    json j;
    j["app"] = "app";
    j["id"] = 1;
    j["document"] = "dasd测试中文支持";
    std::cout << j.dump(4) << std::endl;
}