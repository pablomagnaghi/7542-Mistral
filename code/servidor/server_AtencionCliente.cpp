#include "server_AtencionCliente.h"


#include <string>
#include <iostream>

#include "common_PeticionHTTP.h"
#include "common_RespuestaHTTP.h"
#include "./common_Soap.h"

#include "./../Xml.h"
#include "./../XmlNodo.h"

#include "./../Template.h"
#include "./../DocTemplate.h"
#include "./../Exceptions.h"

#include "./../VisitorPostScript.h"

#include "./../XmlNodeSet.h"


#include "common_Socket.h"
#include "common_Mensajes.h"
#include "common_Thread.h"
#include "server_Server.h"
#include "common_Mutex.h"

#include "server_WebService.h"

  // Códigos de resultado en SOAP
  // 0: OK + rutaDeArchivo
  // 1: No existe version para esa fecha
  // 2: Archivo de datos sin tag
  // 3: No existe template con ese nombre en el sistema

AtencionCliente::AtencionCliente ( Socket* sock ) {
  socket = sock;
}

bool AtencionCliente::validarPeticionHTTP(  PeticionHTTP& peticion, 
					    RespuestaHTTP& respuesta ) {
  if ( peticion.mensajeValido() ) {

    if ( peticion.getTipoPeticion() != METODO_POST ) {
      respuesta.setCodigo( CODE_NOT_IMPLEMENTED );
      respuesta.setDescripcion( DESCRIPCION_NOT_IMPLEMENTED );
      return false;
    }

    if ( peticion.getVersion() != VERSION_PROTOCOLO ) {
      respuesta.setCodigo( CODE_ERROR_VERSION );
      respuesta.setDescripcion( DESCRIPCION_ERROR_VERSION );
      return false;
    }

    std::string header;
    if ( !peticion.getHeaderValue(HEADER_CONTENT_LENGHT,header)  ) {
      respuesta.setCodigo( CODE_LENGTH_REQUIRED );
      respuesta.setDescripcion( DESCRIPCION_LENGTH_REQUIRED );
      return false;
    }

    return true;
  }
  else {
    respuesta.setCodigo( CODE_BAD_REQUEST );
    respuesta.setDescripcion( DESCRIPCION_BAD_REQUEST );
    return false;
  }
}


void AtencionCliente::run() {
  string sockBuffer;
  string msj;

  RespuestaHTTP respuestaHTTP( CODE_BAD_REQUEST, DESCRIPCION_BAD_REQUEST );

  // Valido errores de parseo en el mensaje
  PeticionHTTP* msjHTTP = Mensajes::recibirPeticionHTTP(*socket);

  if ( (msjHTTP) && (validarPeticionHTTP( *msjHTTP, respuestaHTTP ) ) ) {

    WebService webService;
    webService.procesarPeticionSOAP( *msjHTTP, respuestaHTTP );

  }
  if ( msjHTTP )
    delete msjHTTP;

  Mensajes::enviarMsjHTTP(*socket,&respuestaHTTP);
  tryToStop();
}

void AtencionCliente::tryToStop() {
  socket->shutDown();
}

AtencionCliente::~AtencionCliente() {
  delete socket;
}
    
void AtencionCliente::showMessage( const std::string& msg ) const {
  static Mutex mutex_cout;
  mutex_cout.lock();
  std::cout << msg;
  mutex_cout.unlock();
}

