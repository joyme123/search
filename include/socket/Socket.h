#ifndef Socket_class
#define Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;       //最大连接数
const int MAXRECV = 10000;           //接收缓冲区

class Socket{
    private:
        int m_sock;
        sockaddr_in m_addr;
    public:
        Socket();
        virtual ~Socket();

        // Server initialization
        bool create();
        bool bind ( const int port );
        bool listen() const;
        bool accept ( Socket& ) const;

        // Client initialization
        bool connect ( const std::string host, const int port );

        // Data Transimission
        bool send ( const std::string ) const;
        int recv ( std::string& ) const;
        // Binary Data Transimission
        bool sendBinary(char* binaryData,unsigned int length ) const;
        int recvBinary ( char*& cbuf,int& length) const;

        void set_non_blocking ( const bool );

        bool is_valid() const { return m_sock != -1; }
};


#endif