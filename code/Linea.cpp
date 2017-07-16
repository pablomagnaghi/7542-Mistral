#include "Linea.h"
#include "Visitor.h"

Linea::Linea(  int posX, int posY, int cR, int cV, int cA, int borde, int posXfinal, int posYfinal )
:ObjetoGrafico( posX, posY, cR, cV, cA, borde ) {
  this->posXfinal = posXfinal;
  this->posYfinal = posYfinal;
}

Linea::Linea( int posX, int posY )
:ObjetoGrafico( posX, posY, 0, 0, 0, BORDE ) {
  this->posXfinal = LONGITUD;
  this->posYfinal = 0;
}

Linea::Linea( XmlNodo* nodo ) {
  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);
}

Linea::~Linea() {

}

void Linea::accept( Visitor* v ) {
  v->visit( *this );
}

void Linea::agregarAtributos ( XmlNodo* nodo ) {
  ObjetoGrafico::agregarAtributos(nodo);

  XmlNodo nodoPosXfinal("posXfinal");
  nodoPosXfinal.setContenido(this->posXfinal);
  nodo->agregarHijo(nodoPosXfinal);

  XmlNodo nodoPosYfinal("posYfinal");
  nodoPosYfinal.setContenido(this->posYfinal);
  nodo->agregarHijo(nodoPosYfinal);
}

void Linea::obtenerAtributos ( XmlNodo* nodo ) {
  ObjetoGrafico::obtenerAtributos(nodo);

  this->posXfinal = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->posYfinal = nodo->getContenidoInt();
  *nodo = nodo->getHermano();
}

int Linea::getPosXfinal() const {
  return posXfinal;
}
void Linea::setPosXfinal( int posXfinal ) {
  this->posXfinal = posXfinal;
}

int Linea::getPosYfinal() const {
  return posYfinal;
}

void Linea::setPosYfinal( int posYfinal ) {
  this->posYfinal = posYfinal;
}

XmlNodo Linea::toXml() {
  XmlNodo nodo("linea");

  this->agregarPropiedades(&nodo);
  this->agregarAtributos(&nodo);

  return nodo;
}
