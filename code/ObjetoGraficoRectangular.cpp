#include "ObjetoGraficoRectangular.h"
#include <iostream>

ObjetoGraficoRectangular::ObjetoGraficoRectangular( int posX, int posY, int cR,
		int cV, int cA, int borde, int ancho, int alto )
: ObjetoGrafico( posX, posY, cR, cV, cA, borde ) {
  this->ancho = ancho;
  this->alto = alto;
}

ObjetoGraficoRectangular::ObjetoGraficoRectangular()
: ObjetoGrafico() {
  this->ancho = ANCHO;
  this->alto = ALTO;
}

ObjetoGraficoRectangular::~ObjetoGraficoRectangular() {

}

void ObjetoGraficoRectangular::agregarAtributos ( XmlNodo* nodo ) {
  ObjetoGrafico::agregarAtributos(nodo);

  XmlNodo nodoAncho("ancho");
  nodoAncho.setContenido(this->ancho);
  nodo->agregarHijo(nodoAncho);

  XmlNodo nodoAlto("alto");
  nodoAlto.setContenido(this->alto);
  nodo->agregarHijo(nodoAlto);
}

void ObjetoGraficoRectangular::obtenerAtributos ( XmlNodo* nodo ) {
  ObjetoGrafico::obtenerAtributos(nodo);

  this->ancho = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->alto = nodo->getContenidoInt();
  *nodo = nodo->getHermano();
}

int ObjetoGraficoRectangular::getAncho() const {
  return this->ancho;
}

void ObjetoGraficoRectangular::setAncho( int ancho ) {
  this->ancho = ancho;
}

int ObjetoGraficoRectangular::getAlto() const {
  return this->alto;
}

void ObjetoGraficoRectangular::setAlto( int alto ) {
  this->alto = alto;
}
