#include "common_PeticionHTTP.h"

#include <iostream>

#include <string>
using namespace std;

PeticionHTTP::PeticionHTTP( const string& tipo, 
			    const string& path,
			    const string& version ) {
  this->setVersion( version );
  this->setTipoPeticion( tipo );
  this->setPath( path );
}

PeticionHTTP::PeticionHTTP( const std::string& peticion ) 
: MensajeHTTP(peticion) {

  if ( mensajeValido() ) {
    bool resultado = false;
    std::string line;

    if ( this->readLinea( peticion, 0, line ) != string::npos )
	resultado = parseTresCampos( metodo, path, version, line );
    this->setValido( resultado );
  }
}

std::string PeticionHTTP::getTipoPeticion() const {
  return this->metodo;
}

void PeticionHTTP::setTipoPeticion( std::string tipo ) {
  this->metodo = tipo;
}

std::string PeticionHTTP::getVersion() const {
  return this->version;
}


void PeticionHTTP::setVersion( std::string version ) {
  this->version = version;
}

std::string PeticionHTTP::getPath() const {
  return this->path;
}


void PeticionHTTP::setPath( std::string path ) {
  this->path = path;
}

std::string PeticionHTTP::obtenerContentType() const {
  std::string cType;
  this->getHeaderValue(HEADER_CONTENT_TYPE,cType);
  return cType;
}


std::string PeticionHTTP::obtenerContentLenght() const {
  std::string cLength;
  this->getHeaderValue(HEADER_CONTENT_LENGHT,cLength);
  return cLength;
}

std::string& PeticionHTTP::toString( std::string& str ) const {
  str += this->metodo;
  str += ' ';
  str += this->path;
  str += ' ';
  str += this->version;
  MensajeHTTP::toString( str );
  return str;
}
