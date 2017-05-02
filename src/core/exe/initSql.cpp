#include <string>
#include "src/core/db/Mysql.h"
#include "src/core/util/config.h"
/**
 * 初始化数据库的脚本,执行前请先创建好数据库search
 * author:jiangpengfei 
 * date:2017-05-02
 */

void createTable(){
    Mysql mysql;    //初始化mysql对象

    boost::scoped_ptr<sql::Statement> stmt(mysql.getConnection()->createStatement());
    stmt->execute("DROP TABLE IF EXISTS `document`;");
    stmt->execute("CREATE TABLE `document` (`id` int(20) NOT NULL AUTO_INCREMENT,`mongoId` varchar(255) NOT NULL,`srcFlg` int(11) DEFAULT NULL,`title` varchar(1000) NOT NULL,`type` int(2) NOT NULL,`abstract` varchar(255) NOT NULL,`url` text NOT NULL,`author` varchar(255) NOT NULL,`text` mediumtext NOT NULL,`wordNum` int(30) DEFAULT NULL,`updateTime` datetime NOT NULL,`createTime` datetime NOT NULL,PRIMARY KEY (`id`)) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;");

    stmt->execute("DROP TABLE IF EXISTS `simhash`");
    stmt->execute("CREATE TABLE `simhash` (`id` int(30) NOT NULL AUTO_INCREMENT,`simhash` varchar(128) NOT NULL,`docIds` text NOT NULL,`createTime` datetime NOT NULL,`updateTime` datetime NOT NULL,PRIMARY KEY (`id`),UNIQUE KEY `simhash` (`simhash`)) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;");

    stmt->execute("DROP TABLE IF EXISTS `word`");
    stmt->execute("CREATE TABLE `word` (`id` int(20) NOT NULL AUTO_INCREMENT,`word` varchar(255) NOT NULL,`postingList` longtext NOT NULL,`docCount` int(30) NOT NULL,`totalCount` int(30) NOT NULL,PRIMARY KEY (`id`),UNIQUE KEY `word_UNIQUE` (`word`)) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4");
}

int main(){
    createTable();
    return 1;
}