#include "OperandoVariable.h"

OperandoVariable::OperandoVariable( const std::string& xpath ) {
  this->setContenido( xpath );
}

OperandoVariable::OperandoVariable( XmlNodo* nodo ) {
  this->xpath = nodo->getContenido();
}

OperandoVariable::~OperandoVariable() {

}

int OperandoVariable::getValor( XmlNodo*) const {
	return NUM_INVALIDO;
}

void OperandoVariable::setContenido( const std::string& xpath ) {
  this->xpath = xpath;
}

// devuelve el xpath
std::string OperandoVariable::getContenido() const{
  return this->xpath;
}

XmlNodo OperandoVariable::toXml() {
  XmlNodo nodoOperandoVariable("operandoVariable");
  nodoOperandoVariable.setContenido(xpath);

  return nodoOperandoVariable;
}

