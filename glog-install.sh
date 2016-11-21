##glog日志组件
##需要aclocal和automake，有可能存在版本不一致的问题，通过修改Makefile中的版本号即可解决
##test-driver的软连接可能指向位置不正确，重新创建软连接即可
git clone https://github.com/google/glog.git
./configure

##c++连接mysql组件mysql-connnect-cpp(c++)
##这个要安装1.x版本,2.x版本是提供文档存储的接口的