#ifndef RESPUESTAHTTP_H_
#define RESPUESTAHTTP_H_

#include "common_MensajeHTTP.h"

// Algunos codigo de error y sus descripciones
#define CODE_OK			"200"
#define DESCRIPCION_OK		"OK"



#define CODE_BAD_REQUEST	"400"
#define DESCRIPCION_BAD_REQUEST	"Bad Request"

#define CODE_NOT_FOUND		"404"
#define DESCRIPCION_NOT_FOUND	"Not Found"

#define CODE_LENGTH_REQUIRED		"411"
#define DESCRIPCION_LENGTH_REQUIRED	"Length Required"



#define CODE_SERVER_ERROR		"500"
#define DESCRIPCION_SERVER_ERROR	"Internal Server Error"

#define CODE_NOT_IMPLEMENTED	"501"
#define DESCRIPCION_NOT_IMPLEMENTED	"Not Implemented"

#define CODE_ERROR_VERSION	"505"
#define DESCRIPCION_ERROR_VERSION	"HTTP Version Not Supported"





#include <iostream>
#include <string>

#define CHAR1 (char)0xD 
#define CHAR2 (char)0xA
class RespuestaHTTP : public MensajeHTTP {
private:
  std::string version;
  std::string codigo;
  std::string descripcionCodigo;

public:
  RespuestaHTTP(  const std::string& respuesta );

  RespuestaHTTP(  const std::string& codigo,
		  const std::string& descripcionCodigo,
		  std::string version = VERSION_PROTOCOLO );

  std::string getVersion() const;
  void setVersion( const std::string& );

  std::string getCodigo() const;
  void setCodigo( const std::string& );

  std::string getDescripcion() const;
  void setDescripcion( const std::string& );

  std::string& toString( std::string& str ) const;

};

#endif /* RESPUESTAHTTP_H_ */
