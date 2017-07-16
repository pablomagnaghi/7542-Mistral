#include "Xml.h"


// xmlParseFile carga el documento desde el fichero especificado como parámetro
// ejemplo de ruta /home/rodrigo/gastos.xml"
Xml::Xml(const std::string& nombre) {
  context = NULL;
  doc = xmlParseFile(nombre.c_str());

  if ( !doc) 
    throw new XmlArchivoInvalidoExc( nombre );

  this->nodoRaiz = xmlDocGetRootElement( doc );
}

Xml::Xml() {
  context = NULL;
  doc = NULL;
}

bool Xml::valido() const {
  return ( doc != NULL );
}

void Xml::guardar(const std::string& ubicacion) {
  xmlSaveFile(ubicacion.c_str(), doc);
}

// xmlNewDoc crea un nuevo documento xml
void Xml::nuevoDoc (const std::string& version) {
  liberarRecursos();
  doc = xmlNewDoc((const xmlChar*) version.c_str());
  this->nodoRaiz = xmlDocGetRootElement( doc );
}

/**** Métodos relacionados con consutas Xpath *****/


void Xml::crearContextoXpath() {
   if ( !doc )
     throw new ErrorAlAbrirXmlDoc();
  
   if (context != NULL)
      xmlXPathFreeContext(context);
 
   context = xmlXPathNewContext(doc);
}


XmlNodeSet Xml::evaluarExpresion( const std::string& consultaXpath ) {
   if ( !doc )
     throw new ErrorAlAbrirXmlDoc();
   if ( !context )
     throw new DocumentoSinContextoXpathExc();
 
   return  xmlXPathEvalExpression( BAD_CAST consultaXpath.c_str(), context );
}

void Xml::setCurrentNode( XmlNodo& nodo ) {
   if ( !doc )
     throw new ErrorAlAbrirXmlDoc();
   if ( !context )
     throw new DocumentoSinContextoXpathExc();
 
   context->node = nodo.getNodo();
}

XmlNodo Xml::getCurrentNodo() {
   if ( !doc )
     throw new ErrorAlAbrirXmlDoc();
   if ( !context )
     throw new DocumentoSinContextoXpathExc();
 
  return context->node;
}

bool Xml::tieneContextoXpath() const {
  return (context != NULL );
}

Xml::~Xml() {
   liberarRecursos();
   //xmlCleanupParser();

}


// devuelve el nodo raíz del documento
XmlNodo* Xml::getNodoRaiz() {
   if ( !doc )
     throw new ErrorAlAbrirXmlDoc();
  return &nodoRaiz;
}

// xmlDocSetRootElement setea el elemento raíz del documento
void Xml::setNodoRaiz (const std::string& nombre) {
  XmlNodo nodoAux(nombre);
  xmlDocSetRootElement(doc, nodoAux.getNodo());
  nodoRaiz = nodoAux;
}

void Xml::setNodoRaiz ( XmlNodo& nodo ) {
  xmlDocSetRootElement(doc, nodo.getNodo());
  nodoRaiz = nodo;
}

void Xml::toString( std::string& docString ) {
  xmlChar *xmlbuff;
  int buffersize;
  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
  docString = (char*)BAD_CAST xmlbuff;
  xmlFree(xmlbuff);
}

void Xml::fromString( const std::string& docString ) {
  this->liberarRecursos();
  doc = xmlReadMemory(docString.c_str(), docString.size(), "noname.xml", NULL, XML_PARSE_NOBLANKS );
  if ( ! doc )
    throw new XmlArchivoInvalidoExc("string de memoria");
  this->nodoRaiz = xmlDocGetRootElement( doc );

}

// xmlReadMemory analiza un documento XML en memoria y construye un árbol.
// xmlDocGetRootElement devuelve un valor de tipo xmlNodePtr,
// que no es más que un puntero al nodo raiz del documento
Xml::Xml(const char* buffer, int size) {
  context = NULL;
  doc = xmlReadMemory(buffer, size, NULL, NULL, 0);
  XmlNodo r(xmlDocGetRootElement(doc));
  nodoRaiz = r;
}

void Xml::liberarRecursos() {
   if ( doc  )
     xmlFreeDoc(doc);
   if (context != NULL)
     xmlXPathFreeContext(context);
   context = NULL;
}

