#include "Operador.h"

Operador::Operador( const std::string& operador) {
  this->operador = operador;
}

Operador::Operador( XmlNodo* nodo ) {
  this->operador = nodo->getContenido();
}

Operador::~Operador() {

}

int Operador::getValor( XmlNodo*) const {
	return NUM_INVALIDO;
}

std::string Operador::getContenido() const {
  return this->operador;
}

void Operador::setContenido( const std::string& operador ) {
  this->operador = operador;
}

XmlNodo Operador::toXml() {
  XmlNodo nodoOperador("operador");
  nodoOperador.setContenido(this->operador);

  return nodoOperador;
}
