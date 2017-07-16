#include "common_Socket.h"

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

Socket::Socket() {
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

// Servidor
     
bool Socket::bind( const short port )  {
  struct sockaddr_in serv_addr;

  // bzero(&serv_addr.sin_zero, 8); // Lleno de ceros la estructura
  memset((char *)&serv_addr,0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET; // Tipo internet
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  int resBind = ::bind(sockfd,(struct sockaddr *)&serv_addr,(socklen_t)sizeof(struct sockaddr) );

  return (resBind == 0);
}

bool Socket::listen() const {
  return ( ::listen( sockfd,SOMAXCONN ) == 0 );
}

bool Socket::accept( Socket& socket ) const {
  struct sockaddr_in cli_addr;
  unsigned int clilen = (socklen_t)sizeof(cli_addr);
  int newsockfd = ::accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);

  if ( newsockfd >=0 )
	socket.sockfd = newsockfd;

  return ( newsockfd >=0 );
}

// Cliente
bool Socket::connect( const std::string host, const short port ) {
  int resultConnect = (-1);

  struct hostent *he;
  struct sockaddr_in their_addr; // información de la dirección de destino

  if ( (he=gethostbyname(host.c_str()) ) != NULL) {
	their_addr.sin_family = AF_INET;     // Ordenación de bytes de la máquina
	their_addr.sin_port = htons(port); // short, Ordenación de bytes de la red
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), 8, sizeof(int)); // poner a cero el resto de la estructura
	
	resultConnect = ::connect(sockfd, (struct sockaddr *)&their_addr,sizeof(struct sockaddr) );
  }

  return ( resultConnect == 0 );
}

// Data Transimission

int Socket::send ( const std::string& buffer, size_t posStart ) const {
  return ::send( sockfd, buffer.c_str()+posStart, buffer.size()-posStart, 0 );
}

int Socket::recv ( std::string& buffer ) const {
  char c_buffer[ TAM_BUFFER_RECV+1  ];
  int recibidos = ::recv( sockfd, (void*)&c_buffer,TAM_BUFFER_RECV,0 );

  if ( recibidos>0 )
	buffer = c_buffer;

  return recibidos;
}

void Socket::shutDown() {
  shutdown( this->sockfd, SHUT_RDWR );
}

bool Socket::close() {
  return ( ::close(sockfd) == 0 );
}
