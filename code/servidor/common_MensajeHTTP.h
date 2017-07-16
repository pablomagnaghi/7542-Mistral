#ifndef _MENSAJE_HTTP_H_INCLUDED_
#define _MENSAJE_HTTP_H_INCLUDED_

#include <string>
#include <map>
#include "./../Xml.h"

#define SP	' '
#define CRLF 	"\r\n"
#define FINAL 	"\r\n\r\n"

#define VERSION_PROTOCOLO "HTTP/1.0"

// Headers comunes
#define HEADER_CONTENT_TYPE "Content−Type"
#define VALUE_CONTENT_TYPE	"application/soap+xml; charset=utf−8"

#define HEADER_CONTENT_LENGHT "Content-Length"

class MensajeHTTP {

private:
  std::map<std::string,std::string> headerLines;
  std::string messageBody;

  bool msjValido;

public:


  static bool parseTresCampos( std::string&, std::string&, 
			       std::string&, const std::string& line );
  size_t readLinea( const std::string& cadena, size_t pos, std::string& line );
  bool cargarHeader( const std::string& header, std::string& nombre, std::string& valor );
  std::string& sacarEspacios( std::string& cadena );
  size_t getFinPalabra( const std::string& cadena, size_t pos );

  MensajeHTTP( const std::string& mensaje );

  MensajeHTTP();

  bool mensajeValido();
  void setValido( bool valido = true );

  bool getHeaderValue( const std::string& headerName, int& headerValue ) const;
  bool getHeaderValue( const std::string& headerName, std::string& headerValue ) const;
  void setHeaderValue( const std::string& headerName, const std::string& headerValue );

  void getMessageBody( std::string& ) const;
  void getMessageBody( Xml& archivoXml ) const;

  void setMessageBody( const std::string& body );
  void setMessageBody( Xml& archivoXml );

  void SetContentTypeForSoapXml();
  void SetContentLenght( int );

  void clear();
  virtual std::string& toString( std::string& str ) const;
  virtual ~MensajeHTTP();
};

#endif
