# dsearch-一个用c++实现的搜索引擎

目前实现的功能:

    1.使用mysql存储倒排索引
    2.分词
    3.单个单词查询
    4.simhash的计算
    5.正文提取
    6.关键字提取(最普通的TF-IDF与余弦相似性)
    7.stopword的去除

TODOList:

    1.多查询词
    2.PageRank

### **使用了以下的开源项目的代码**

 - c语言下的分词项目: friso,项目地址:https://git.oschina.net/lionsoul/friso
 - json工具:Json for Modern c++,项目地址:https://github.com/nlohmann/json
 - c++实现的cityHash,项目地址:https://github.com/google/cityhash
 
### **运行环境中需要的依赖库**
 - 日志库:glog,项目地址:https://github.com/google/glog.git
 - cgi库:cgicc,代码地址:ftp://ftp.gnu.org/gnu/cgicc/cgicc-3.2.9.tar.gz
 - mysql连接工具:mysql-connector-c++,项目地址:https://github.com/mysql/mysql-connector-cpp
 - redis客户端:cpp_redis,项目地址:https://github.com/cylix/cpp_redis
 - mongodb的连接库:mongocxx,项目地址:https://github.com/mongodb/mongo-cxx-driver.git
