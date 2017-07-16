#include "DocTemplate.h"

#include "Xml.h"
#include "XmlNodo.h"
#include "Template.h"
#include "Fecha.h"

#include <string>
#include <iostream>

using namespace std;

#define NOMBRE_NODO		"docTemplate"
#define NOMBRE_TAG_NOMBRE	"nombre"
#define NOMBRE_TAG_DESC		"descripcion"
#define NOMBRE_TAG_DATOS  	"tagDatos"

// Genera el xml que representa al documento.

XmlNodo DocTemplate::toXml() {
  XmlNodo nodo( NOMBRE_NODO );

  XmlNodo nodoNombre( NOMBRE_TAG_NOMBRE );
  nodoNombre.setContenido(this->nombre);
  nodo.agregarHijo(nodoNombre);

  XmlNodo nodoDescripcion( NOMBRE_TAG_DESC );
  nodoDescripcion.setContenido(this->descripcion);
  nodo.agregarHijo(nodoDescripcion);

  XmlNodo nodoXpathDatos( NOMBRE_TAG_DATOS );
  nodoXpathDatos.setContenido( this->xpathNodoDatos );
  nodo.agregarHijo(nodoXpathDatos);

  for(unsigned int i = 0; i < misTemplates.size(); i++)
    nodo.agregarHijo( misTemplates[i]->toXml() );

  return nodo;
}

// Abre un archivo xml, y carga los distintos templates e información
// que contenga.Si se abre en solo lectura, no se persiste al cerrar el
//  documento.

DocTemplate::DocTemplate( const string& path ) {
  this->docValido = false;

  try {
    // Abro el archivo
    Xml docXml( path );
    this->docValido = true;

    XmlNodo* nodoRaiz = docXml.getNodoRaiz();
    XmlNodo::verificarNombre( NOMBRE_NODO, *nodoRaiz );

    XmlNodo nodo = nodoRaiz->getHijo();
    XmlNodo::verificarNombre( NOMBRE_TAG_NOMBRE, nodo );
    this->nombre = nodo.getContenido();

    nodo = nodo.getHermano();
    XmlNodo::verificarNombre( NOMBRE_TAG_DESC, nodo );
    this->descripcion = nodo.getContenido();

    nodo = nodo.getHermano();
    XmlNodo::verificarNombre( NOMBRE_TAG_DATOS, nodo );
    this->xpathNodoDatos = nodo.getContenido();
    nodo = nodo.getHermano();

    // archivo listo para cargar el DocTemplate
    // cargo los atributos del doc.
    while (nodo.esValido()) {
      Template* miTemplate = new Template( &nodo );
      this->agregarVersion(miTemplate);
      nodo = nodo.getHermano();
    }
  } 
  catch ( XmlArchivoInexistenteExc* ex ) {
    delete ex;
    throw new DocTemplateArchivoInexistenteExc( path );
  } 
  catch ( XmlArchivoInvalidoExc* ex ) {
    delete ex;
    throw new DocTemplateInvalidoExc( path );
  }
}

DocTemplate::DocTemplate( const string& nombre, const string& descripcion, 
			  const std::string& xpathNodoDatos ) {
  this->nombre = nombre;
  this->descripcion = descripcion;
  this->xpathNodoDatos = xpathNodoDatos;
  this->docValido = true;
}
  
DocTemplate::~DocTemplate() {
  if ( docValido ) {
    vector<Template*>::iterator it = misTemplates.begin();
    while ( it!=misTemplates.end() ) {
      delete (*it);
      it++;
    }
    misTemplates.clear();
  }
}

// Devuelve true si se logró abrir y cargar el documento.

bool DocTemplate::isOpen() const {
  return this->docValido;
}

// Guarda el DocTemplate si es que se no se abrió en modo de soloLectura.
// Utiliza el método privado toXml()::Xmlodo*

void DocTemplate::saveAs( const std::string& path ) {
  if ( docValido ) {
    Xml docXml;
    docXml.nuevoDoc();
    XmlNodo nodoDoc = this->toXml();
    docXml.setNodoRaiz( nodoDoc );
    docXml.guardar( path );
  }
}

Template* DocTemplate::getVersion( Fecha& f ) {
  Template* t = NULL;

  if ( docValido ) {
    vector<Template*>::iterator it = misTemplates.begin();

    while ( (it!=misTemplates.end()) && (!t) ) {
      if ( f.pertenece( (*it)->getValidoDesde(), (*it)->getValidoHasta() ) ) {
        t = (*it);
      }
      it++;
    }
  }
  return t;
}
  
Template* DocTemplate::getVersion( unsigned int pos ) {
  Template* t = NULL;
  if ( misTemplates.size() >pos )
    t = misTemplates[pos];

  return t;
}

int DocTemplate::getCantidadDeVersiones() {
  return this->misTemplates.size();
}

void DocTemplate::agregarVersion( Template* t ) {
  this->misTemplates.push_back( t );
}

const string& DocTemplate::getNombre() const {
  return this->nombre;
}

void DocTemplate::setNombre( const std::string& nombre ) {
  this->nombre = nombre;
}

const string& DocTemplate::getDescripcion() const {
  return this->descripcion;
}

void DocTemplate::setDescripcion( const std::string& descripcion ) {
  this->descripcion = descripcion;
}

std::string DocTemplate::getXpathNodoDatos() const {
  return xpathNodoDatos;
}

void DocTemplate::setXpathNodoDatos( const std::string& xpath ) {
  xpathNodoDatos = xpath;
}
