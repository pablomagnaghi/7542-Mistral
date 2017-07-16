#ifndef _MENSAJES_H_INCLUDED_
#define _MENSAJES_H_INCLUDED_

#include "common_Socket.h"
#include <string>

#define CHAR_FIN_MSJ	'\t'
#define CHAR_REPLACE_ENDL   'z'

#include "common_MensajeHTTP.h"
#include "common_PeticionHTTP.h"


  // Protocolo de mensajes entre cliente y servidor de id's.
  // Los metodos de construccion de mensajes aseguran que el caracter CHAR_FIN_MSJ
  // no esta en el mensaje.Asi, los metodos para enviar y recibir pueden interpretar el
  // final de un mensaje con CHAR_FIN_MSJ.

class Mensajes {
public:
  static bool enviarMsjHTTP( Socket& sock, MensajeHTTP* msj  );
  static PeticionHTTP* recibirPeticionHTTP( Socket& sock );

  // Envia el mensaje pasado por parametro al socket.
  // Si no se logr? enviar el mensaje a travez del socket devuelve false.
  // Para enviar el msj le concatena el CHAR_FIN_MSJ.Es necesario que el mensaje
  // no contenga ning?n caracter CHAR_FIN_MSJ.

  static bool enviarMsj( Socket& sock, const std::string& msj );

  // Recibe un mensaje enviado con enviarMsj(...).
  // Devuelve false si falla la lectura del socket.
  // Recibe un buffer con los bytes que no hayan sido procesados en la lectura
  // anterior y deja en el buffer los bytes que no pertenezcan al msj.

  static bool recibirMsj( Socket& sock, std::string& msj, std::string& buffer );

  static bool recibirMsjDeSize( Socket& sock, std::string& msj, int size, std::string& buffer );

  // Recibe una cadena campos separados por un caracter delim y
  // carga en el vector los distintos campos.
  // Retorna la cantidad de campos encontrados.
  static size_t parseCampos( const std::string& str, char delim,
		  std::string* v_campos, size_t size_v );

  // Transforma una cadena en un entero,

  static int strToInt( const std::string& calificacionStr );

private:

  // Reemplaza un caracter en la cadena.
  static void replace( std::string&, char caracterBuscado, char nuevoCaracter );
};

#endif


