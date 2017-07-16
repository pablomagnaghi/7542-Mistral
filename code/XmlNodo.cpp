#include "XmlNodo.h"
#include <iostream>
#include "Exceptions.h"

std::string XmlNodo::getStringFromInt (int num) {
  std::stringstream buf;
  buf << num;
  return buf.str();
}

int XmlNodo::getIntFromString(const std::string& cadena) {
  int pos;
  std::stringstream buffer(cadena);
  buffer >> pos;
  return pos;
}

XmlNodo::XmlNodo(xmlNodePtr nodo) {
  this->nodo = nodo;
  tieneNs = false;
}

XmlNodo::XmlNodo(const std::string& nombre) {
  nodo = xmlNewNode(NULL, (xmlChar*) nombre.c_str());
  tieneNs = false;
}
  
XmlNodo::XmlNodo(XmlNodo nodoPadre, const std::string& nombre ) {
  if (nodoPadre.tieneNs) {
    nodo = xmlNewChild(nodoPadre.getNodo(), nodoPadre.ns,
    		(const xmlChar*) nombre.c_str(), NULL );
    this->ns = nodoPadre.ns;
    tieneNs = true;
  } else {
	  nodo = xmlNewChild(nodoPadre.getNodo(), NULL,
			  (const xmlChar*) nombre.c_str(), NULL);
	  tieneNs = false;
  }
}


XmlNodo::XmlNodo(XmlNodo nodoPadre, const std::string& nombre, const std::string& contenido) {
  if (nodoPadre.tieneNs) {
    nodo = xmlNewChild(nodoPadre.getNodo(), nodoPadre.ns,
    		(const xmlChar*) nombre.c_str(), (const xmlChar*) contenido.c_str());
    this->ns = nodoPadre.ns;
    tieneNs = true;
  } else {
	  nodo = xmlNewChild(nodoPadre.getNodo(), NULL,
			  (const xmlChar*) nombre.c_str(), (const xmlChar*) contenido.c_str());
	  tieneNs = false;
  }
}

XmlNodo::XmlNodo() {
  tieneNs = false;
}

XmlNodo::~XmlNodo() {
}

xmlNodePtr& XmlNodo::getNodo() {
  return nodo;
}

void XmlNodo::agregarHijo(const std::string& nombre, const std::string& contenido) {
  if (tieneNs) {
    xmlNewChild(nodo, ns, (const xmlChar*) nombre.c_str(), (const xmlChar*) contenido.c_str());
    }
  else
	xmlNewChild(nodo, NULL, (const xmlChar*) nombre.c_str(), (const xmlChar*) contenido.c_str());
}

void XmlNodo::agregarHijo(XmlNodo nodoHijo) {
  if ( !this->nodo )
    throw new NullNodeExc();
  xmlAddChild(nodo, nodoHijo.getNodo());
}

XmlNodo XmlNodo::getHijo() {
  if ( !this->nodo )
    throw new NullNodeExc();
  return this->getNodo()->xmlChildrenNode;
}

XmlNodo XmlNodo::getHermano() {
  if ( !this->nodo )
    throw new NullNodeExc();
  return xmlNextElementSibling(nodo);
}

//  retorna null si no tiene contenido
std::string XmlNodo::getContenido() {
  if ( !this->nodo )
    throw new NullNodeExc();

  xmlChar* aux = xmlNodeGetContent(nodo);

  if ( !aux )
    throw new NotElementNodeExc( this->getNombre() );

  std::string c = (char*)BAD_CAST aux;
  xmlFree( aux );
  return c;
}

// devuelve el contenido como entero
int XmlNodo::getContenidoInt() {
  if ( !this->nodo )
    throw new NullNodeExc();

  std::string aux = getContenido();

  if ( aux.size() == 0)
    throw new ContenidoIntVacioExc( this->getNombre() );

  return getIntFromString (aux);
}

bool XmlNodo::getContenidoBool() {
  if ( !this->nodo )
    throw new NullNodeExc();

  std::string aux = getContenido();

  if ( aux.size() == 0)
    throw new ContenidoIntVacioExc( this->getNombre() );

  if ( aux == XML_BOOL_TRUE )
    return true;
  else if ( aux == XML_BOOL_FALSE )
    return false;


  throw new ContenidoBoolInvalidoExc( this->getNombre() );
}


std::string XmlNodo::getNombre() {
 if ( !this->nodo )
    throw new NullNodeExc();
  xmlChar* aux = BAD_CAST nodo->name;
  return std::string((char*) aux);	
}

std::string XmlNodo::getPropiedad(const std::string& nombre) {
  char* propiedad;
  propiedad = (char*) xmlGetProp(nodo, (const xmlChar*) nombre.c_str());
  std::string resultado(propiedad);
  xmlFree(propiedad);// ver este tema de memoria
  return resultado;
}

// devuelve la propiedad como entero
int XmlNodo::getPropiedadInt(const std::string& nombre) {
  std::string aux = getPropiedad(nombre);

  if (aux.size())
    return getIntFromString (aux);
  else {
    return -1;
    // aca puede devolver -1 o nada porque el usuario ya sabe
  }
}

void XmlNodo::setPropiedad(const std::string& nombre, const std::string& valor) {
  xmlSetProp(nodo, (const xmlChar*) nombre.c_str(), (const xmlChar*) valor.c_str());
}

// en vez de un string, recibe un int y lo transforma internamente a string
void XmlNodo::setPropiedad(const std::string& nombre, int valor) {
  std::string aux = getStringFromInt(valor);
  setPropiedad(nombre, aux);
}

//  se puede setear mas de un namesapace
void XmlNodo::setNameSpace(const std::string& nombre, const std::string& valor) {
  //ns = xmlNewNs(nodo,(xmlChar*)"http://schemas.xmlsoap.org/soap/envelope/",(xmlChar*)"soap");
  tieneNs = true;
  ns = xmlNewNs(nodo, (xmlChar*) valor.c_str(), (xmlChar*) nombre.c_str());
  xmlSetNs(nodo, ns);
}

// Si el nodo al cual agrego contenido tiene hijo o contenido,
// este se reemplaza por el contenido
void XmlNodo::setContenido(const std::string& contenido) {
  xmlNodeSetContent(nodo, (const xmlChar*) contenido.c_str());
  //xmlSetc(nodo, (const xmlChar*) nombre.c_str(),(const xmlChar*) valor.c_str());
}

// primero transforma el int a un string y luego si el nodo al cual
// agrego contenido tiene hijo o contenido, este se reemplaza por el contenido
void XmlNodo::setContenido(int contenido) {
  xmlNodeSetContent(nodo, (const xmlChar*) this->getStringFromInt(contenido).c_str());
  //xmlSetc(nodo, (const xmlChar*) nombre.c_str(),(const xmlChar*) valor.c_str());
}


void XmlNodo::setContenido( bool& contenido) {
  std::string boolString;
  if ( contenido )
    boolString = XML_BOOL_TRUE;
  else
    boolString = XML_BOOL_FALSE;
  this->setContenido( boolString );
}


bool XmlNodo::esValido () {
  return ( nodo != NULL );
}
