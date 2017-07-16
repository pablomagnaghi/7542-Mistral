#include "common_RespuestaHTTP.h"
#include <iostream>

RespuestaHTTP::RespuestaHTTP(  const std::string& respuesta )
: MensajeHTTP( respuesta ) {

  if ( mensajeValido() ) {
    bool resultado = false;
    std::string line;

    if ( this->readLinea( respuesta, 0, line ) != std::string::npos )
	resultado = parseTresCampos( version, codigo, descripcionCodigo, line );
    this->setValido( resultado );
  }

}


RespuestaHTTP::RespuestaHTTP(  const std::string& codigo,
		const std::string& descripcionCodigo,
		std::string version ) {
  this->codigo = codigo;
  this->descripcionCodigo = descripcionCodigo;
  this->version = version;
}

std::string RespuestaHTTP::getVersion() const {
  return this->version;
}

void RespuestaHTTP::setVersion( const std::string& v ) {
  version = v;
}

std::string RespuestaHTTP::getCodigo() const {
  return this->codigo;
}

void RespuestaHTTP::setCodigo( const std::string& codigo ) {
  this->codigo = codigo;
}

std::string RespuestaHTTP::getDescripcion() const {
  return this->descripcionCodigo;
}

void RespuestaHTTP::setDescripcion( const std::string& descripcionCodigo ) {
  this->descripcionCodigo = descripcionCodigo;
}


std::string& RespuestaHTTP::toString( std::string& str ) const {
  str += this->version;
  str += ' ';
  str += this->codigo;
  str += ' ';
  str += this->descripcionCodigo;

  MensajeHTTP::toString( str );
  return str;
}
