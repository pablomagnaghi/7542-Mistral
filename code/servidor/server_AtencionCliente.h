#ifndef _ATENCION_CLIENTE_H_INCLUDED_
#define _ATENCION_CLIENTE_H_INCLUDED_


#include "common_Socket.h"
#include "common_Thread.h"

#include <string>
#include "./../Xml.h"

#define MSJ_ERROR       "error"
#define MSJ_OK          "ok"


 // Códigos de resultado en SOAP
 // 0: OK + rutaDeArchivo
 // 1: No existe version para esa fecha
 // 2: Archivo de datos sin tag
 // 3: No existe template con ese nombre en el sistema

#define RETURN_SOAP_OK			0
#define RETURN_SOAP_SIN_VERSION		1
#define RETURN_SOAP_SIN_TAG_DATOS	2
#define RETURN_SOAP_SIN_TEMPLATE	3
#define RETURN_SOAP_ERROR_PETICION	4

#include "common_PeticionHTTP.h"
#include "common_RespuestaHTTP.h"


  // Su tarea es recibir las comandos del cliente, procesarlos y devolver
  // los resultados.


class AtencionCliente : public Thread {
private:
  Socket* socket;
    
  bool validarPeticionHTTP( PeticionHTTP& peticion, RespuestaHTTP& respuesta );

public:
  // Recibe un socket abierto del cliente con el que se debe comunicar
  // y un registroRestaurantes sobre el que ejecuta las acciones y
  // obtiene la información.
  AtencionCliente ( Socket* sock );

  // Cierra el socket.Asegura que despues se puede hacer un join
  // del thread y este terminará correctamente.

  void tryToStop();

  ~AtencionCliente();

  void showMessage( const std::string& ) const;
protected:
  // Recibe un mensaje a través del socket, lo procesa y devuelve una
  // respuesta.El msj se procesa con el método procesarMensaje(---).
  // Despues de retornar una respuesta vuelve a escuchar mensajes.
  void run();
};
#endif
