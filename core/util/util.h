#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<cppconn/connection.h>

using namespace std;

void printSqlError(sql::SQLException e){
    cout << "error happend:" << e.getErrorCode() <<" : " << e.what() << endl;
}

#endif
