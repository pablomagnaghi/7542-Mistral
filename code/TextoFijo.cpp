#include "TextoFijo.h"
#include "Visitor.h"

TextoFijo::TextoFijo( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto,
		int size, const std::string& tipoFuente, const std::string& texto )
: Texto ( posX, posY, cR, cV, cA, borde, ancho, alto, size, tipoFuente ) {
  this->texto = texto;
}

TextoFijo::TextoFijo( const std::string& texto )
: Texto (){
  this->texto = texto;
}

ObjetoGraficoRectangular* TextoFijo::clone() {
  return new TextoFijo( *this );
}

TextoFijo::TextoFijo(XmlNodo* nodo) {
  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);
}

TextoFijo::~TextoFijo() {

}

void TextoFijo::accept( Visitor* v ) {
  v->visit( *this );
}

void TextoFijo::agregarAtributos ( XmlNodo* nodo ) {
  Texto::agregarAtributos (nodo);

  XmlNodo nodoTexto("texto");
  nodoTexto.setContenido(this->texto);
  nodo->agregarHijo(nodoTexto);
}

void TextoFijo::obtenerAtributos ( XmlNodo* nodo ) {
  Texto::obtenerAtributos (nodo);

  this->texto = nodo->getContenido();
  *nodo = nodo->getHermano();
}

std::string TextoFijo::getTexto() const {
  return texto;
}

void TextoFijo::setTexto(const std::string& texto) {
  this->texto = texto;
}

XmlNodo TextoFijo::toXml() {
  XmlNodo nodo("textoFijo");

  this->agregarPropiedades(&nodo);

  this->agregarAtributos(&nodo);

  return nodo;
}

std::string TextoFijo::toString() const {
  return this->texto;
}

int TextoFijo::getId() const {
  return 0;
}
