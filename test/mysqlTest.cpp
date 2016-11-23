#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <cppconn/metadata.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>   

#include <mysql_driver.h>
#include <mysql_connection.h>

using namespace std;

int main(int argc,const char **argv){
    const string url = "tcp://127.0.0.1:3306";
    const string user = "5019";
    const string password = "5019";
    const string database = "empdb";
    
    size_t row;
    stringstream sql;
    stringstream msg;
    int i;

    try{
        sql::Driver* driver = sql::mysql::get_driver_instance();

        boost::scoped_ptr<sql::Connection> con(driver->connect(url,user,password));
        boost::scoped_ptr<sql::Statement> stmt(con->createStatement());

        stmt->execute("USE "+database);
        stmt->execute("DROP TABLE IF EXISTS test");
        stmt->execute("CREATE TABLE test(id INI,label CHAR(1))");
        
        cout << "\t Test表创建成功" << endl;
        
        for(i = 0; i < 200; i++){
            sql.str("");
            sql << "INSERT INTO test(id,label)VALUES(";
            sql << i+1 <<", '" << i << "')";
            stmt->execute(sql.str()); 
        }    

        cout << "插入数据成功" << endl;

        {
            boost::scoped_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id,label FROM test ORDER BY id ASC"));
            cout << "记录数为" << res->rowsCount() <<endl;
            
            row = 0;
            while(res->next()){
                cout << "row: " << row;
                cout << "id: "  << res->getInt(1);
                cout << "lable: " << res->getString("lable") <<endl;
                row++;
            }

        }
    }catch(sql::SQLException &e){
        cout << e.what() << e.getErrorCode() << e.getSQLState() << endl;
    }catch(std::runtime_error &e){
        cout << "运行出错" << endl;
    }
}
