#include "common_MensajeHTTP.h"

#include <sstream>
#include <string>
#include <map>
#include "./../Xml.h"

using namespace std;

MensajeHTTP::MensajeHTTP( const string& mensaje ) {
  setValido();

  std::string linea;
  std::string nombre;
  std::string valor;

  size_t pos = 0;
  pos = readLinea( mensaje, pos, linea );
  pos = readLinea( mensaje, pos, linea );

  while ( (pos!=string::npos) && (linea!="")&&(msjValido) ) {
    if ( cargarHeader( linea, nombre, valor ) )
      this->setHeaderValue( sacarEspacios(nombre), sacarEspacios(valor) );
    else
      setValido( false );

    pos = readLinea( mensaje, pos, linea );
  }
  if ( linea != "" ) {
    if ( cargarHeader( linea, nombre, valor ) )
      this->setHeaderValue( sacarEspacios(nombre), sacarEspacios(valor) );
    else
      setValido( false );
  }
  else if ( pos != string::npos ) {
    this->setMessageBody( mensaje.substr(pos) );
  }
}

MensajeHTTP::MensajeHTTP() {
  setValido( true );
}
 

void MensajeHTTP::setValido( bool valido ) {
  this->msjValido = valido;
}


bool MensajeHTTP::mensajeValido() {
  return msjValido;
}

bool MensajeHTTP::getHeaderValue( const string& headerName, string& headerValue ) const {
  
  map<string,string>::const_iterator it;
  it = this->headerLines.find( headerName );
  
  bool resultado = ( it != this->headerLines.end() );

  if ( resultado )
    headerValue = it->second;

  return resultado;
}

bool MensajeHTTP::getHeaderValue( const string& headerName, int& headerValue ) const {
  std::string valorStr;
  bool resultado = getHeaderValue( HEADER_CONTENT_LENGHT, valorStr );
  if ( resultado ) {
    stringstream sstr;
    sstr << valorStr;
    sstr >> headerValue;
  }
  return resultado;
}

void MensajeHTTP::setHeaderValue( const string& headerName, const string& headerValue ) {
  this->headerLines[ headerName ] = headerValue;
}

void MensajeHTTP::getMessageBody( std::string& msg ) const {
  msg = messageBody;
}

void MensajeHTTP::getMessageBody( Xml& archivoXml ) const {
  archivoXml.fromString( this->messageBody );
}

void MensajeHTTP::setMessageBody( const std::string& body ) {
  messageBody = body;
}

void MensajeHTTP::setMessageBody( Xml& archivoXml ) {
  archivoXml.toString( messageBody );
}


void MensajeHTTP::SetContentTypeForSoapXml() {
  this->setHeaderValue(HEADER_CONTENT_TYPE,VALUE_CONTENT_TYPE);
}

void MensajeHTTP::SetContentLenght( int valor ) {
  std::stringstream ss;
  ss << valor;
  std::string str;
  ss >> str;
  this->setHeaderValue(HEADER_CONTENT_LENGHT, str);

}

std::string& MensajeHTTP::toString( std::string& str ) const {
  map<string,string>::const_iterator it;
  it = this->headerLines.begin();

  while ( it!= headerLines.end() ) {
    str += CRLF;
    str += it->first;
    str += ": ";
    str += it->second;
    it++;
  }
     str += CRLF;
     str += CRLF;

   if ( messageBody != "" ) {
     str += this->messageBody;
   }
  return str;
}

MensajeHTTP::~MensajeHTTP() {
  this->headerLines.clear();
}


size_t MensajeHTTP::readLinea( const string& cadena, size_t pos, string& line ) {
    size_t finLinea;
    if ( pos < cadena.size() ) {
      finLinea = cadena.find( CRLF, pos  );
      line = cadena.substr( pos, finLinea - pos );
    } else {
      finLinea = string::npos;
    }
    if ( finLinea != string::npos )
      finLinea += 2;
    return finLinea;
}

void MensajeHTTP::clear() {
  this->headerLines.clear();
}

string& MensajeHTTP::sacarEspacios( string& cadena ) {
  size_t sizeCadena = cadena.size();
  size_t startPalabra = 0;
  while ( (startPalabra<sizeCadena) && (cadena[startPalabra]==' ' ) ) {
    startPalabra++;
  }

  if ( startPalabra == sizeCadena )
    cadena = "";
  else {
    size_t endPalabra = sizeCadena-1;
    while ( (endPalabra>0) && (cadena[endPalabra]==' ' ) ) {
      endPalabra--;
    }

    cadena = cadena.substr( startPalabra, endPalabra-startPalabra+1 );
  }

  return cadena;
}


bool MensajeHTTP::cargarHeader( const string& header, string& nombre, string& valor ) {
  bool resultado = false;
  size_t posSeparador = header.find(':');
  if ( posSeparador != string::npos ) {
    nombre = header.substr( 0, posSeparador );
    if ( posSeparador<header.size()-1 )
      valor = header.substr( posSeparador+1 );
    else
      valor = "";
    resultado = true;
  }

  return resultado;
}

size_t MensajeHTTP::getFinPalabra( const std::string& cadena, size_t pos ) {
  size_t sizeCadena = cadena.size();
  if ( pos < sizeCadena ) {
    while ( (pos<sizeCadena) && (cadena[pos]==' ') )
      pos++;
      pos++;
  }
  pos = cadena.find( ' ', pos+1 );
  return pos;
}

bool MensajeHTTP::parseTresCampos( std::string& str1, std::string& str2, 
				   std::string& str3, const std::string& line ) {

  bool resultado = false;
  size_t posPrimerEspacio = line.find( SP );

  if ( posPrimerEspacio < line.size()-1 ) {    

    size_t posSegundoEspacio = line.find( SP, posPrimerEspacio+1 );

    if ( posSegundoEspacio != string::npos ) {

      if (  line.find( SP, posSegundoEspacio+1 ) == string::npos ) {
	resultado = true;
	str1 = line.substr( 0 , posPrimerEspacio);
	str2 = line.substr(posPrimerEspacio+1,posSegundoEspacio-posPrimerEspacio-1);
	str3 = line.substr(posSegundoEspacio+1);
      }
    }
  }

  return resultado;
}
