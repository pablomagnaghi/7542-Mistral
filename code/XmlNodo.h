#ifndef XMLNODO_H_
#define XMLNODO_H_
#include <libxml2/libxml/tree.h>
#include <iostream>
#include <sstream>
#include "Exceptions.h"

#define XML_BOOL_TRUE	"true"
#define XML_BOOL_FALSE	"false"
class XmlNodo {
private:
  xmlNodePtr nodo;
  xmlNsPtr ns;
  // tiene namespace
  bool tieneNs;
  std::string getStringFromInt (int num);
  int getIntFromString (const std::string& cadena);

public:
  XmlNodo(xmlNodePtr nodo);
  XmlNodo(const std::string& nombre);
  XmlNodo(XmlNodo nodoPadre, const std::string& nombre, const std::string& contenido);
  XmlNodo(XmlNodo nodoPadre, const std::string& nombre );

  XmlNodo();
  virtual ~XmlNodo();

  xmlNodePtr& getNodo();
  void agregarHijo(const std::string& nombre, const std::string& contenido);
  void agregarHijo(XmlNodo nodoHijo);
  XmlNodo getHijo();
  XmlNodo getHermano();

  std::string getContenido();
  std::string getNombre();
  int getContenidoInt() ;
  bool getContenidoBool();

  std::string getPropiedad(const std::string& nombre);
  int getPropiedadInt(const std::string& nombre);

  void setPropiedad(const std::string& nombre, const std::string& valor);
  void setPropiedad(const std::string& nombre, int valor);

  void setNameSpace(const std::string& nombre, const std::string& valor);

  void setContenido(const std::string& contenido);
  void setContenido(int contenido);
  void setContenido(bool& contenido);

  bool esValido();

  static void verificarNombre( const std::string& nombre, XmlNodo& nodo ) {
    if ( nodo.getNombre() != nombre )
      throw new NodoXmlIncorrectoExc( nombre, nodo.getNombre() );
  }
};
#endif
