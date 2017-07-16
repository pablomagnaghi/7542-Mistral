#include "OperandoConstante.h"

OperandoConstante::OperandoConstante( const int& valor ) {
  setValor( valor );
}

OperandoConstante::OperandoConstante( XmlNodo* nodo ) {
  this->valor = nodo->getContenidoInt();
}

OperandoConstante::~OperandoConstante() {

}

int OperandoConstante::getValor( XmlNodo* ) const {
  return this->valor;
}

void OperandoConstante::setValor( const int& valor ) {
  this->valor = valor;
}

std::string OperandoConstante::getContenido() const {
  return "";
}

void OperandoConstante::setContenido( const std::string& contenido) {
  std::stringstream buffer(contenido);
  buffer >> this->valor;
}

XmlNodo OperandoConstante::toXml() {
  XmlNodo nodoOperandoConstante("operandoConstante");
  nodoOperandoConstante.setContenido(this->valor);

  return nodoOperandoConstante;
}
