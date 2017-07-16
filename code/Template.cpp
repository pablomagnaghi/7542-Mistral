#include "Template.h"

#include "Fecha.h"
#include "XmlNodo.h"

#include "Linea.h"
#include "TextoFijo.h"
#include "TextoVariable.h"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#define NOMBRE_NODO		"template"
#define NOMBRE_TAG_DESDE	"desde"
#define NOMBRE_TAG_HASTA 	"hasta"
#define NOMBRE_TAG_DESCRIPCION 	"descripcion"
#define NOMBRE_TAG_HOJA		"hoja"

// Crea un Template a partir de un nodo existente.

Template::Template( XmlNodo* nodo ) {

  if ( !nodo ) {
    this->descripcion = "Un template de prueba con una linea,un txtFijo y uno variable";
    this->hoja = new Hoja( MAXANCHO, MAXALTO, "a4" );
    Linea* linea = new Linea(100,100,5,10,15,2,100,0);
    TextoFijo* tf = new TextoFijo("Hola que tal");
    TextoVariable* tv = new TextoVariable("//item/precio");
    hoja->agregarObjeto( linea );
    hoja->agregarObjeto( tf );
    hoja->agregarObjeto( tv );
  }
  else {
    XmlNodo::verificarNombre( NOMBRE_NODO, *nodo );
    // primero creo la fecha desde
    XmlNodo nodoAux = nodo->getHijo();
    this->desde.setDia(nodoAux.getContenidoInt());
    nodoAux = nodoAux.getHermano();
    this->desde.setMes(nodoAux.getContenidoInt());
    nodoAux = nodoAux.getHermano();
    this->desde.setAnnio(nodoAux.getContenidoInt());

    // creo la fecha hasta
    nodoAux = nodoAux.getHermano();
    this->hasta.setDia(nodoAux.getContenidoInt());
    nodoAux = nodoAux.getHermano();
    this->hasta.setMes(nodoAux.getContenidoInt());
    nodoAux = nodoAux.getHermano();
    this->hasta.setAnnio(nodoAux.getContenidoInt());

    nodoAux = nodoAux.getHermano();
    XmlNodo::verificarNombre( NOMBRE_TAG_DESCRIPCION, nodoAux );
    this->descripcion = nodoAux.getContenido();

    nodoAux = nodoAux.getHermano();
    XmlNodo::verificarNombre( NOMBRE_TAG_HOJA, nodoAux );

    XmlNodo nodoUnaHoja = nodoAux.getHijo();
    this->hoja = new Hoja( &nodoUnaHoja );
  }
}

// Crea un template nuevo con un alto y ancho de hoja.

Template::Template( int ancho, int alto, const Fecha& desde, 
		    const Fecha& hasta, const string desc ) {
  this->hasta = hasta;
  this->desde = desde;
  this->descripcion = desc;

  this->hoja = new Hoja( ancho, alto, "a4" );
}

Template::Template( string tipoHoja, const Fecha& desde, 
		    const Fecha& hasta, const string desc  ) {

  this->hasta = hasta;
  this->desde = desde;
  this->descripcion = desc;

  //  FIXME: ver tamannio de acuerdo a tipoHoja
  this->hoja = new Hoja( MAXANCHO, MAXALTO, "a4" );
}

// Retorna un objeto gráfico que representa a la hoja del template
// y contine todos los objetos gráficos.

Hoja* Template::getHoja() {
  return this->hoja;
}

const Fecha& Template::getValidoDesde() const {
  return this->desde;
}
  
void Template::setValidoDesde( const Fecha& desde ) {
  this->desde = desde;
}

const Fecha& Template::getValidoHasta() const {
  return this->hasta;
}

void Template::setValidoHasta( const Fecha& hasta ) {
  this->hasta = hasta;
}

void Template::setDescripcion( const std::string& d ) {
  this->descripcion = d;
}

const std::string& Template::getDescripcion() const {
  return this->descripcion;
}

std::string Template::toString() const {
  std::stringstream sstr;
  sstr << desde;
  sstr << " --> ";
  sstr << hasta;
  return sstr.str();
}


XmlNodo Template::toXml() {
  XmlNodo nodo( NOMBRE_NODO );

  XmlNodo nodoFechaDesdeDia("fechaDesdeDia");
  nodoFechaDesdeDia.setContenido( this->desde.getDia() );
  nodo.agregarHijo(nodoFechaDesdeDia);

  XmlNodo nodoFechaDesdeMes("fechaDesdeMes");
  nodoFechaDesdeMes.setContenido(this->desde.getMes());
  nodo.agregarHijo(nodoFechaDesdeMes);

  XmlNodo nodoFechaDesdeAnnio("fechaDesdeAnnio");
  nodoFechaDesdeAnnio.setContenido(this->desde.getAnnio());
  nodo.agregarHijo(nodoFechaDesdeAnnio);

  XmlNodo nodoFechaHastaDia("fechaHastaDia");
  nodoFechaHastaDia.setContenido(this->hasta.getDia());
  nodo.agregarHijo(nodoFechaHastaDia);

  XmlNodo nodoFechaHastaMes("fechaHastaMes");
  nodoFechaHastaMes.setContenido(this->hasta.getMes());
  nodo.agregarHijo(nodoFechaHastaMes);

  XmlNodo nodoFechaHastaAnnio("fechaHastaAnnio");
  nodoFechaHastaAnnio.setContenido(this->hasta.getAnnio());
  nodo.agregarHijo(nodoFechaHastaAnnio);

  XmlNodo nodoDescripcion( NOMBRE_TAG_DESCRIPCION );
  nodoDescripcion.setContenido(this->descripcion);
  nodo.agregarHijo(nodoDescripcion);

  XmlNodo nodoHoja( NOMBRE_TAG_HOJA );
  nodoHoja.agregarHijo( this->hoja->toXml() );
  nodo.agregarHijo( nodoHoja );

  return nodo;
}

Template::~Template() {
  delete hoja;
}

