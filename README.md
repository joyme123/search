# dsearch-一个用c++实现的搜索引擎


### **使用了以下的开源项目的代码**

 - c语言下的分词项目: friso,项目地址:https://git.oschina.net/lionsoul/friso
 - json工具:Json for Modern c++,项目地址:https://github.com/nlohmann/json
 - c++实现的cityHash,项目地址:https://github.com/google/cityhash
 
### **运行环境中需要的依赖库**
 - 日志库:glog,项目地址:https://github.com/google/glog.git
 - cgi库:cgicc,代码地址:ftp://ftp.gnu.org/gnu/cgicc/cgicc-3.2.9.tar.gz
 - mysql连接工具:mysql-connector-c++,项目地址:https://github.com/mysql/mysql-connector-cpp

## **依赖库安装指导**

### **glog日志组件**
注意事项:
需要aclocal和automake，有可能存在版本不一致的问题，通过修改Makefile中的版本号即可解决
test-driver的软连接可能指向位置不正确，重新创建软连接即可
aclocal的安装可以参考这里:https://askubuntu.com/questions/45480/how-do-i-install-aclocal/47952
安装指令:
 > git clone https://github.com/google/glog.git
 
 > ./configure
 
 > make
 
 > sudo make install

 glog默认的日志位置在/tmp/下，若要指定日志输出位置可以通过设置环境变量的方式,但是要给指定目录写的权限。如果想看全部的，可以在源码的logging.cc文件下看到）：
> GLOG_logtostderr bool，默认为FALSE，将日志打印到标准错误，而不是日志文件
GLOG_alsologtostderr bool，默认为FALSE，将日志打印到日志文件，同时也打印到标准错误
GLOG_stderrthreshold int，默认为2（ERROR），大于等于这个级别的日志才打印到标准错误，当指定这个参数时，GLOG_alsologtostderr参数将会失效
GLOG_minloglevel int，默认为0（INFO）， 小于这个日志级别的将不会打印
GLOG_log_dir string类型，指定日志输出目录，目录必须存在 
GLOG_max_log_size int，指定日志文件最大size，超过会被切割，单位为MB
GLOG_stop_logging_if_full_disk bool，默认为FALSE，当磁盘满了之后不再打印日志
GLOG_v int，默认为0，指定GLOG_v=n时，对vlog(m)，当m<=n时才会打印日志

```
export GLOG_log_dir=log
export GLOG_minloglevel=1
export GLOG_stderrthreshold=1
export GLOG_v=3
export GLOG_max_log_size=1
```
### **cgicc是支持cgi的c++库**

 > wget ftp://ftp.gnu.org/gnu/cgicc/cgicc-3.2.9.tar.gz
 
 > tar -xvf cgicc-3.2.9.tar.gz

 > ./configure --prefix=/usr
 
 > make

 如果出现无法获取'html/index.html' 的文件状态(stat)的错误，则执行

 > touch doc/html/index.html           #make出错执行这一步再make

 > sudo make install 



 apache需要开启对cgi的支持,并将网站根目录指向www,将cgi执行目录指向cgi-bin

### **c++连接mysql组件mysql-connnect-cpp(c++)**
这个要安装1.x版本,2.x版本是提供文档存储的接口的
具体安装过程请看我的博客,里面介绍了2.x和1.x版本的安装
[linux下编译安装mysql-connector-cpp](http://www.myway5.com/index.php/2017/04/19/linux-complier-mysql-connector-cpp/)

### redis客户端
[redis的客户端地址](https://github.com/cylix/cpp_redis)
[安装说明](https://github.com/Cylix/cpp_redis/wiki/Mac-&-Linux-Install)
- cpp_redis需要一个一个叫做tacopie的tcp库，以及pthread库,安装tacopie的库文档在这里[tacopie库](https://github.com/Cylix/tacopie)
```
#redis和tacopie的安装命令
#注意事项:cpp_redis和tacopie的CmakeList.txt生成的是静态库.a,应该更改STATIC为SHARED,同时在CMakeList中的编译选项上使用-fPIC选项:
# 克隆工程
git clone https://github.com/Cylix/cpp_redis.git
# 进入到工程目录
cd cpp_redis
# 获取tacopie的子模块
git submodule init && git submodule update
# 创建build目录并进入
mkdir build && cd build
# 使用cmake生成makefile
cmake .. -DCMAKE_BUILD_TYPE=Release
# 编译库
make
# 安装库
make install
```
### mongodb客户端
mongodb客户端使用的是mongocxx，mongocxx是基于[mongoc](http://mongoc.org/libmongoc/current/installing.html)包装的c++的客户端，
所以这里需要安装mongoc之后，再安装[mongocxx_3.0.x](https://github.com/mongodb/mongo-cxx-driver),
[mongodb文档](http://mongoc.org/libmongoc/current/tutorial.html#making-a-connection)
- 需要libbson的库，源代码在这里[libbson](https://github.com/mongodb/libbson),因为mongocxx对libbson的库的版本要求是>1.5.0的，所以我们需要从源代码安装1.6.2的版本。
```
libbson的安装命令（这一步可以不进行，因为在mongo-c的安装过程中会自动检测libbson并安装）
git clone https://github.com/mongodb/libbson.git
cd libbson
git checkout r1.6
./autogen.sh
cd build
cmake ..
make
sudo make install

```

```
#mongo-c的安装命令
git clone https://github.com/mongodb/mongo-c-driver.git
cd mongo-c-driver
git checkout r1.6
./autogen.sh --with-libbson=bundled
make 
sudo make install

```

```
#mongo-cxx-driver的安装命令
git clone https://github.com/mongodb/mongo-cxx-driver.git \
    --branch releases/stable --depth 1
cd mongo-cxx-driver/build
cmake -DCMAKE_BUILD_TYPE=Release -DBSONCXX_POLY_USE_BOOST=1 \
    -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
sudo make install
```

###libconfig的安装

```
git clone https://github.com/hyperrealm/libconfig.git
cd libconfig
#使用make编译,如果提示
make
```