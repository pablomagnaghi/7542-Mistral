#ifndef _SOCKET_H_INCLUDED_
#define _SOCKET_H_INCLUDED_

#include <string>

#define TAM_BUFFER_RECV 255

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

class Socket {
private:
  int sockfd;

  // No se permite la copia de un socket.

  Socket( const Socket& );
  Socket& operator= ( const Socket& );

public:
  Socket();

  // Servidor
  bool bind( const short port );
  bool listen() const;
  bool accept( Socket& socket ) const;
  // Cliente
  bool connect( const std::string host, const short port );

  // Data Transimission
  int send ( const std::string& buffer, size_t posStart = 0 ) const;
  int recv ( std::string& buffer ) const;
  void shutDown();
  bool close();
};
#endif

