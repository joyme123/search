#include<iostream>
#include<cpp_redis/cpp_redis>

using namespace std;

int main(){
    cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
    cpp_redis::redis_client client;

    client.connect("127.0.0.1", 6379, [](cpp_redis::redis_client&) {
        std::cout << "client disconnected (disconnection handler)" << std::endl;
    });

    // same as client.send({ "SET", "hello", "42" }, ...)
    client.set("hello", "42", [](cpp_redis::reply& reply) {
        std::cout << "set hello 42: " << reply << std::endl;
        // if (reply.is_string())
        //   do_something_with_string(reply.as_string())
    });

    // same as client.send({ "DECRBY", "hello", 12 }, ...)
    client.decrby("hello", 12, [](cpp_redis::reply& reply) {
        std::cout << "decrby hello 12: " << reply << std::endl;
        // if (reply.is_integer())
        //   do_something_with_integer(reply.as_integer())
    });

    std::string result;

    // same as client.send({ "GET", "hello" }, ...)
    client.get("hello", [&result](cpp_redis::reply& reply) {
        std::cout << "get hello: " << reply << std::endl;
        if (reply.is_string()){
            std::cout << "是字符串" << std::endl;
            result = reply.as_string();
            std::cout << result << std::endl;
        }else{
            std::cout << "不是字符串" << std::endl;
        }
    });


    // commands are pipelined and only sent when client.commit() is called
    //client.commit();

    // synchronous commit, no timeout
    client.sync_commit();

    std::cout << "提交后获取的结果是:" + result << std::endl;

    // synchronous commit, timeout
    // client.sync_commit(std::chrono::milliseconds(100));

    return 0;
}