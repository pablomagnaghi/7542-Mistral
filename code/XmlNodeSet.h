#ifndef _XML_NODE_SET_H_INCLUDED_
#define _XML_NODE_SET_H_INCLUDED_


#include <libxml/xpath.h>
#include "XmlNodo.h"

// Conjunto de nodos como resultado de una consulta Xpath.

class XmlNodeSet {
private:
  xmlXPathObjectPtr result;

public:

  XmlNodeSet( xmlXPathObjectPtr result );


  // Cantidad de nodos de resultado

  int size();

  // Acceso relatio a los nodos-
  // pos va desde 0 .. size()-1
  // Si pos queda fuera de rango lanza IndexFueraDeRangoEnNodeSetExc

  XmlNodo getNodo( int pos );

  ~XmlNodeSet();
};

#endif
