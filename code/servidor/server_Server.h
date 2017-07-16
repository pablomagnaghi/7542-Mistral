#ifndef _SERVER_H_INCLUDED_
#define _SERVER_H_INCLUDED_

#include "common_Thread.h"

#include "common_Socket.h"
#include "server_AtencionCliente.h"

#include <list>
using namespace std;

  // Servidor de identificación que permite atender múltiples clientes usando
  // el protocolo definido en Mensajes.h.

class Server : public Thread {

private:
  Socket socket;
  short port;

  list<AtencionCliente*> misConexiones;

  bool running;

  // Libera los threads de todos los clientes, tanto aquellos que esten corriendo
  // como los que no.

  void liberarClientes();

public:  
  Server(short port);
  void tryToStop();
  bool isRunning();

protected:
  void run();
};

#endif

