#include "TextoVariable.h"
#include "Visitor.h"

TextoVariable::TextoVariable( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto,
		int size, const std::string& tipoFuente, const std::string& textoXpath )
: Texto ( posX, posY, cR, cV, cA, borde, ancho, alto, size, tipoFuente ) {
  this->setTextoXpath( textoXpath );
}

TextoVariable::TextoVariable( std::string textoXpath )
: Texto (){
  this->setTextoXpath( textoXpath );
}

ObjetoGraficoRectangular* TextoVariable::clone() {
  return new TextoVariable( *this );
}

// Primero obtengo el hijo, y a partir de ahi, cada atributo nuevo es un hermano
TextoVariable::TextoVariable(XmlNodo* nodo) {
  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);
}

TextoVariable::~TextoVariable() {

}

void TextoVariable::accept( Visitor* v ) {
  v->visit( *this );
}

void TextoVariable::agregarAtributos ( XmlNodo* nodo ) {
  Texto::agregarAtributos (nodo);

  XmlNodo nodoTextoXpath("textoXpath");
  nodoTextoXpath.setContenido(this->textoXpath);
  nodo->agregarHijo(nodoTextoXpath);
}

void TextoVariable::obtenerAtributos ( XmlNodo* nodo ) {
  Texto::obtenerAtributos (nodo);

  this->textoXpath = nodo->getContenido();
  *nodo = nodo->getHermano();
}

void TextoVariable::setTextoXpath(const std::string& textoXpath) {
  this->textoXpath = textoXpath;
}

std::string TextoVariable::getTextoXpath() {
  return this->textoXpath;
}

XmlNodo TextoVariable::toXml() {
  XmlNodo nodo("textoVariable");

  this->agregarPropiedades(&nodo);

  this->agregarAtributos(&nodo);

  return nodo;
}

std::string TextoVariable::toString() const {
  return this->textoXpath;
}

int TextoVariable::getId() const {
  return COD_UNO;
}
