#ifndef SOAP_H_
#define SOAP_H_

#include <iostream>

#include "./../Xml.h"
#include "./../XmlNodo.h"

class Soap {
private:
  Xml* soapXml;
  XmlNodo* header;
  XmlNodo* body;
public:
  Soap( Xml& );
  
  void agregarHijoBody ( XmlNodo );

  void setPropiedadBody ( const std::string&, int );
  void setPropiedadBody ( const std::string&, const std::string& );

  void guardar();

  virtual ~Soap();
};

#endif
