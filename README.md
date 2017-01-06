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
[linux下编译安装mysql-connector-cpp](http://myway5.com/?post=56)


### **文档添加协议**
这个搜索引擎本身是没有文档的添加功能的，所以需要通过外部程序按照一定的规则将文档加入到索引代码中进行索引。

为了支持爬虫和索引服务器的分离，使用socket通信，满足进程间或者网络间的数据传输。根据TCP协议的特点，传输的数据之间可能出现"粘包",为了解决粘包问题，制定了以下的传输协议。

数据包使用二进制流传输,一个数据包分为头部(head)和内容(body)两部分，其中body部分是文档的全部信息，头部主要是为了给分包算法提供支持

**head**

head共有4个字节组成(固定4个字节)，两个部分
 - 第一部分：version,1个字节，代表当前协议的版本号，1~127
 - 第二部分：length，3个字节，代表body部分的<font color="red">长度(请看下方的解释)</font>,0~16777216,这部分需要注意的是，3个字节必须填满，比如body部分的值是20，则传过来的length二进制为00000000 00000000 00010100。

 > 这里的长度指的是body部分以byte为单位的长度

**body**

body部分是一段有指定格式的文本:url\ntype\ncontent
即读到的第一个\n之前的body部分的数据为文档的地址
读到的第一个\n和第二个\n之间的数据为文档的类型，
type = 1 为html网页文档
type = 2 为pdf文档
type = 3 为word文档
之后的内容为网页的全部内容

**java实现的客户端代码示例**:https://github.com/joyme123/search/blob/master/doc/java_socket_client_implement.md
