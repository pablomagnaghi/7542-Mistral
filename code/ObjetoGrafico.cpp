#include "ObjetoGrafico.h"
#include "Constantes.h"

ObjetoGrafico::ObjetoGrafico( int x, int y, int cR, int cV, int cA, int borde ) {
  this->posX = x;
  this->posY = y;
  this->colorRojo = cR;
  this->colorVerde = cV;
  this->colorAzul = cA;
  this->borde = borde;
}

ObjetoGrafico::ObjetoGrafico() {
  this->posX = POSX;
  this->posY = POSY;
  this->colorRojo = 0;
  this->colorVerde = 0;
  this->colorAzul = 0;
  this->borde = BORDE;
}

ObjetoGrafico::~ObjetoGrafico() {

}

void ObjetoGrafico::agregarPropiedades (XmlNodo* nodo) {
  nodo->setPropiedad("posx",this->posX);
  nodo->setPropiedad("posy",this->posY);
}

void ObjetoGrafico::obtenerPropiedades (XmlNodo* nodo) {
  this->posX = nodo->getPropiedadInt("posx");
  this->posY = nodo->getPropiedadInt("posy");
}

void ObjetoGrafico::agregarAtributos ( XmlNodo* nodo ) {
  XmlNodo nodoColorRojo("colorRojo");
  nodoColorRojo.setContenido(this->colorRojo);
  nodo->agregarHijo(nodoColorRojo);

  XmlNodo nodoColorVerde("colorVerde");
  nodoColorVerde.setContenido(this->colorVerde);
  nodo->agregarHijo(nodoColorVerde);

  XmlNodo nodoColorAzul("colorAzul");
  nodoColorAzul.setContenido(this->colorAzul);
  nodo->agregarHijo(nodoColorAzul);

  XmlNodo nodoBorde("borde");
  nodoBorde.setContenido(this->borde);
  nodo->agregarHijo(nodoBorde);
}

void ObjetoGrafico::obtenerAtributos ( XmlNodo* nodo ) {
  this->colorRojo = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->colorVerde = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->colorAzul = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->borde = nodo->getContenidoInt();
  *nodo = nodo->getHermano();
}

int ObjetoGrafico::getPosX() const {
  return posX;
}

int ObjetoGrafico::getPosY() const {
  return posY;
}

void ObjetoGrafico::setPosX(int posX) {
  this->posX = posX;
}

void ObjetoGrafico::setPosY(int posY) {
  this->posY = posY;
}

int ObjetoGrafico::getColorRojo() const {
  return colorRojo;
}

void ObjetoGrafico::setColorRojo( int color ) {
  colorRojo = color;
}

int ObjetoGrafico::getColorVerde() const {
  return colorVerde;
}

void ObjetoGrafico::setColorVerde( int color ) {
  colorVerde = color;
}

int ObjetoGrafico::getColorAzul() const {
  return colorAzul;
}

void ObjetoGrafico::setColorAzul( int color ) {
  colorAzul = color;
}

int ObjetoGrafico::getBorde() const {
  return this->borde;
}

void ObjetoGrafico::setBorde( int borde  ) {
  this->borde = borde;
}
