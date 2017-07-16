#include "server_Server.h"

#include "common_Thread.h"

#include "common_Socket.h"
#include "server_AtencionCliente.h"

#include <iostream>
#include <list>

void Server::liberarClientes() {
  std::list<AtencionCliente*>::iterator it = misConexiones.begin();

  while ( it != misConexiones.end() ) {
    // Indico al thread que pare su ejecución.
    (*it)->tryToStop();
    // Espero a que termine.
    (*it)->join();
    // Libero la memoria asociada al thread.
    delete (*it);
    it++;
  }
  misConexiones.clear();
}

Server::Server( short port ) {
  this->port = port;
  running = true;
}

void Server::tryToStop() {
  socket.shutDown();
  running = false;
}

bool Server::isRunning() {
  return running;
}

void Server::run() {
  running = true;

  bool result = socket.bind( this->port );
  if (result) result = socket.listen();

  while ( (result) && (running) ) {
    Socket* s = new Socket();

    if (socket.accept(*s) ) {
      AtencionCliente* ac = new AtencionCliente(s);
      misConexiones.push_back(ac);
      ac->start();
    }
    else {
      delete s;
    }
  }
  liberarClientes();
  running = false;
}
