/**
 * filename:SimHashDAO.h
 * SimHash数据库查询类的头文件
 * author:jiangpengfei12@gmail.com
 * date:2017-02-07
 */
#ifndef _DOCUMENTDAO_H
#define _DOCUMENTDAO_H

#include<iostream>
#include<string>
#include<glog/logging.h>
#include"Mysql.h"
#include"SimHash.h"
#include"util/util.h"

class SimHashDAO{
    private:
    std::string TABLE = "simhash";
    Mysql* mysql;
    public:
		SimHashDAO(Mysql mysql);
        
        /**
         * 新增SimHash
         * @param simHash simHash码
         * @return int 新增的simHash id值
         */
        int addSimHash(SimHash simHash); 
        
        /**
         * 删除simHash码
         * @param id 要删除的simHash
         * @return int 受影响被删除的记录数
         */
        int deleteSimHash(unsigned int id);   
        
        /**
         * 解析simHash并更新
         * @param simHash 要更新的simHash
         * @return int 受影响的记录数
         */
        int parseSimHashAndUpdate(SimHash simHash); 
		
		/**
         * 搜索SimHash
         * @param id 搜索指定id的simHash
         * @return SimHash 搜索SimHash值
		 */
		SimHash searchSimHash(int id);
};

#endif
