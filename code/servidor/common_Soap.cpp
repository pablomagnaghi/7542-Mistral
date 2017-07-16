#include "common_Soap.h"

//xmlns:env="http://www.w3.org/2003/05/soap-envelope"
Soap::Soap( Xml& miSoapXml ) {
  this->soapXml = &miSoapXml;
  soapXml->nuevoDoc();
  soapXml->setNodoRaiz("Envelope");
  // creo en nodo raiz con el namespace: "soap" y
  // la descripcion de namespace: "http://www.w3.org/2003/05/soap-envelope"
  soapXml->getNodoRaiz()->setNameSpace( "soapenv","http://schemas.xmlsoap.org/soap/envelope/" );

  //soapXml.getNodoRaiz()->setPropiedad( "encodingStyle", "http://www.w3.org/2003/05/soap-encoding");
  header = new XmlNodo( *soapXml->getNodoRaiz(), "Header");
  body = new XmlNodo(*soapXml->getNodoRaiz(),"Body");
}


void Soap::agregarHijoBody ( XmlNodo nodo ) {
  this->body->agregarHijo( nodo );
}

void Soap::setPropiedadBody ( const std::string& nombre, int valor ) {
  this->body->setPropiedad( nombre, valor );
}

void Soap::setPropiedadBody ( const std::string& nombre, const std::string& valor ) {
  this->body->setPropiedad( nombre, valor );
}

void Soap::guardar(){
  soapXml->guardar("miSoap.xml");
}

Soap::~Soap() {
  delete header;
  delete body;
}
