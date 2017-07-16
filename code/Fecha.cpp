#include "Fecha.h"

#include <iostream>
#include "Exceptions.h"

Fecha::Fecha()
: dia(MAX_FECHA), mes(MAX_FECHA), annio(MAX_FECHA) {
}

Fecha::Fecha( int dia, int mes, int annio )
: dia(dia), mes(mes), annio(annio) {
}

Fecha::Fecha( const std::string& fecha ) {
  this->fecha = fecha;
  this->obtenerCampos();
  if ( !esValida() )
    throw new FechaInvalidaException();
}

void Fecha::revisarFecha() {
  if ( dia <= 0 || dia > MAX_DIA )
	this->crearFechaInvalida();
  if ( mes <= 0 || mes > DICIEMBRE )
	this->crearFechaInvalida();
}

void Fecha::crearFechaInvalida() {
  this->dia = 0;
  this->mes = 0;
  this->annio = 0;
}

bool Fecha::esValida() const {
  return !( (dia==0)||(mes==0)||(annio==0));
}

void Fecha::obtenerCampos() {
  if ( fecha.size() == FECHA ) {
    if ( fecha.find("/") == POS ) {
      std::stringstream bufferDia( fecha.substr( 0, POS ) );
      bufferDia >> dia;
      fecha.replace( 0, POS + 1, "" );
      if ( fecha.find("/") == POS ) {
    	std::stringstream bufferMes( fecha.substr( 0, POS ) );
    	bufferMes >> mes;
    	fecha.replace( 0, POS + 1, "" );
    	std::stringstream bufferAnnio( fecha.substr( 0, POS_ANNIO ) );
    	bufferAnnio >> annio;
    	fecha.clear();
      }
      else crearFechaInvalida();
    }
    else crearFechaInvalida();
  }
  else crearFechaInvalida();

  revisarFecha();

}

bool Fecha::operator>( const Fecha& f ) const {
  
  if ( f.annio > annio )
    return false;
  else if ( f.annio < annio )
    return true;

  if ( f.mes > mes )
    return false;
  else if ( f.mes < mes )
    return true;
  
  if ( f.dia > dia )
    return false;
  else if ( f.dia < dia )
    return true;

  return true;
}

// primero reviso si el año es correcto, luego si año se encuentra entre fecha inicial y final
// la fecha pertenece, si es igual el año inicial y final reviso los meses, y en el caso de que
// los meses sean iguales se controlan los dias
  
bool Fecha::pertenece( const Fecha& fechaInicial, const Fecha& fechaFinal ) const {

  return ( ((*this)>fechaInicial) && (!((*this)>fechaFinal)) );

}

int Fecha::getDia() const {
  return this->dia;
}

void Fecha::setDia( int dia ) {
  this->dia = dia;
}

int Fecha::getMes() const {
  return this->mes;
}

void Fecha::setMes( int mes ) {
  this->mes = mes;
}

int Fecha::getAnnio() const {
  return this->annio;
}

void Fecha::setAnnio( int annio ) {
  this->annio = annio;
}

std::ostream& operator<<( std::ostream& stream, const Fecha& f ) {
  if ( (f.getDia()==MAX_FECHA) || (f.getMes()==MAX_FECHA) || (f.getAnnio()==MAX_FECHA) )
    stream << "*";
  else
    stream << f.getDia() << "/" << f.getMes() << "/" << f.getAnnio();
  return stream;
}
