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
         *
         */
        int addSimHash(SimHash simHash); 
        
        /**
         *
         */
        int deleteSimHash(unsigned int id);   
        
        /**
         *
         */
        int parseSimHashAndUpdate(SimHash simHash); 
		
		/**
         *
		 */
		SimHash searchSimHash(int id);
};

#endif
