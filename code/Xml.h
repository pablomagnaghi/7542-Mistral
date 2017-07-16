#ifndef XML_H_
#define XML_H_
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>
#include <iostream>
#include "XmlNodo.h"
#include "XmlNodeSet.h"
#include "Exceptions.h"

class Xml {
private:
  XmlNodo nodoRaiz;
  xmlDocPtr doc;
  void imprimirNombresNodo(xmlNode* nodo);

  xmlXPathContextPtr context;

public:

  // Crea un xml
  // nombre es el nombre de un archivo que se desea abrir y parsear
  // Si el archivo no existe lanza XmlArchivoInexistenteExc
  // Si el archivo no es un Xml valido lanza XmlArchivoInvalidoExc
  Xml(const std::string& nombre);

  // Crea un doc. vacio, llamar a nuevoDoc
  Xml();

  bool valido() const;

  // Libera recursos del doc y del context Xpath si es necesario
  void liberarRecursos();

  virtual ~Xml();


  // Metodos asociados a consultas Xpath


  // Crea un contexto Xpath a partr del documento

  void crearContextoXpath();

  // Evalúa una sentencia Xpath y devuelve un conjunto de nodos
  // como resultado.

  XmlNodeSet evaluarExpresion( const std::string& );


  // Modificar el currentNode del contexto Xpath

  void setCurrentNode( XmlNodo& );
  XmlNodo getCurrentNodo();
  bool tieneContextoXpath() const;

  // vierte un documento XML a un archivo
  void guardar(const std::string& ubicacion);

  // devuelve el nodo raíz del documento
  XmlNodo* getNodoRaiz();

  void setNodoRaiz (const std::string& nombre);
  void setNodoRaiz ( XmlNodo& );

  // Convierte el documento xml a un string y lo devuelve
  void toString( std::string& docString );
  void fromString( const std::string& docString );

  // crea un nuevo documento xml
  void nuevoDoc (const std::string& version = "1.0" );


  // Crea un documento xml a partir del buffer y su tamaño
  // llamando a la función xmlReadMemory y xmlDocGetRootElement de libxml
  Xml(const char* buffer, int size);


};
#endif
