// Definition of the Socket class

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
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket
{
private:
  int m_sock;
  sockaddr_in m_addr;

public:
  Socket();
  virtual ~Socket();

  // Server initialization
  bool create();
  bool bind(const int port); // 与客户端建立连接
  bool listen() const; // 等待来自客户端的连接请求
  bool accept(Socket &) const; // 

  // Client initialization
  bool connect(const std::string host, const int port); // 客户端连接服务端

  // Data Transimission
  bool send(const std::string) const;
  int recv(std::string &) const;

  void set_non_blocking(const bool);

  bool is_valid() const { return m_sock != -1; }
};

#endif