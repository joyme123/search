#ifndef _DOCUMENTDAO_H
#define _DOCUMENTDAO_H

#include<iostream>
#include<string>
#include<glog/logging.h>
#include"Mysql.h"
#include"SimHash.h"
#include"util/util.h"

class SimHashDAO:public Mysql{
    private:
    std::string TABLE = "simhash";
    public:
		SimHashDAO();
        
        /**
         *
         */
        int addSimHash(SimHash simHash); 
        
        /**
         *
         */
        int deleteSimHash(int id);   
        
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
