#include "common_Mensajes.h"

#include "common_Socket.h"

#include <sstream>
#include <string>
#include <iostream>

#include "common_PeticionHTTP.h"


bool Mensajes::enviarMsjHTTP( Socket& sock, MensajeHTTP* msj  ) {

  bool resultado = false;
  if ( msj ) {
    std::string msjSerializado;
    msj->toString( msjSerializado );
    resultado = Mensajes::enviarMsj( sock, msjSerializado );
  }
  return resultado;
}
    
PeticionHTTP* Mensajes::recibirPeticionHTTP( Socket& sock ) {

  PeticionHTTP* msjResultado = NULL;
  std::string mensajeSerializado;
  std::string buffer;

  // Recibo un mensaje HTTP hasta la línea vacía
  bool resultadoOk = recibirMsj(sock,mensajeSerializado,buffer);

  if ( resultadoOk ) {

    // Parseo el mensaje y verifico que sea válido
    msjResultado = new PeticionHTTP(mensajeSerializado);
    resultadoOk = msjResultado->mensajeValido();

    if ( resultadoOk ) {

      int sizeBody = 0;

      if ( msjResultado->getHeaderValue(HEADER_CONTENT_LENGHT,sizeBody) ) {

	std::string body;
	resultadoOk = recibirMsjDeSize( sock,body,sizeBody,buffer );
	if (  resultadoOk ) {
	  msjResultado->setMessageBody( body );
	}
      }

    }
  }

  if ( (msjResultado) && (!resultadoOk) ) {
    delete msjResultado;
    msjResultado = NULL;
  }

  return msjResultado;
}

bool Mensajes::recibirMsjDeSize( Socket& sock, std::string& msj, int size, std::string& buffer ) {
  std::string strLeidos;
  int leidos = 1;
  size_t posFinMsj = std::string::npos;
  size_t sizeBuffer = buffer.size();

  posFinMsj = std::string::npos;

  if ( (int)buffer.size() >= size )
      posFinMsj = size;

  while ( (leidos>0) && (posFinMsj == std::string::npos) ) {
    leidos = sock.recv( strLeidos );
    if ( leidos > 0 ) {
      buffer += strLeidos.substr(0,leidos);
      if ( (int)buffer.size() >= size )
	posFinMsj = size;
      sizeBuffer += leidos;
    }
  }

  if ( leidos > 0 ) {
    msj = buffer.substr( 0, posFinMsj );

    if ( posFinMsj<sizeBuffer-1 )
      buffer = buffer.substr( posFinMsj );
    else
      buffer.clear();
  }

  return ( leidos>0 );
}

bool Mensajes::enviarMsj( Socket& sock, const std::string& msj ) {
  std::string msjAEnviar;
  msjAEnviar = msj;

  //msjAEnviar += CHAR_FIN_MSJ;
  // Envío el msj a través del socket
  int sizeMsj = msjAEnviar.size();
  int enviados = 0;
  int totalEnviados= 0;

  while ( (enviados>=0) && (totalEnviados<sizeMsj) ) {
    enviados = sock.send( msjAEnviar, enviados );
    totalEnviados += enviados;
    std::cout.flush(); 
  }

  return ( totalEnviados == sizeMsj );
}

bool Mensajes::recibirMsj( Socket& sock, std::string& msj, std::string& buffer ) {
  std::string strLeidos;
  int leidos = 1;
  size_t posFinMsj = std::string::npos;
  size_t sizeBuffer = buffer.size();

  posFinMsj = buffer.find( FINAL, 0 );
  while ( (leidos>0) && (posFinMsj == std::string::npos) ) {
    leidos = sock.recv( strLeidos );
    if ( leidos > 0 ) {
      buffer += strLeidos.substr(0,leidos);
      posFinMsj = buffer.find( FINAL, 0 );
      sizeBuffer += leidos;
    }
  }

  if ( leidos > 0 ) {
    msj = buffer.substr( 0, posFinMsj+4 );

    if ( posFinMsj<sizeBuffer-1 )
      buffer = buffer.substr( posFinMsj+4 );
    else
      buffer.clear();
  }

  return ( leidos>0 );
}

void Mensajes::replace( std::string& str, char caracterBuscado, char nuevoCaracter ) {
  size_t size = str.size();
  for ( size_t i = 0; i<size; i++ )
    if ( str[i] == caracterBuscado )
      str[i] = nuevoCaracter;
}


size_t Mensajes::parseCampos( const std::string& str, char delim,
                              std::string* v_campos, size_t size_v ) {
    
  size_t numCampo,startCampo, size, pos;

  numCampo = startCampo = pos = 0;
  size = str.size();

  // recorro la cadena buscando un delimitador
  while ( (pos <= size) && (numCampo<size_v) ) {
    // Cuando lo enc agrego un campo al vector
    if ( ( (pos == size)&&(pos>startCampo) ) || (str[pos] == delim)  ) {
      v_campos[ numCampo ] = str.substr( startCampo, pos-startCampo );
      startCampo = pos+1;
      numCampo++;
    }
    pos++;
  }

  if ( (numCampo>1) && (str[size-1]!=delim) )
    numCampo--;

  return numCampo;
}


int Mensajes::strToInt( const std::string& calificacionStr ) {
  int calificacion = 0;
  if ( calificacionStr.size() > 0 ) {
    std::stringstream str;
    str << calificacionStr;
    str >> calificacion;
  }
  return calificacion;
}

