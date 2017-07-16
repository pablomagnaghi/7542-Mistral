#include "Texto.h"
#include <iostream>

Texto::Texto( int posX, int posY, int cR, int cV, int cA, int borde, int ancho,
		int alto, int size, const std::string& tipoFuente )
: ObjetoGraficoRectangular( posX, posY, cR, cV, cA, borde, ancho, alto ) {
  this->size = size;
  this->tipoFuente = tipoFuente;
}

Texto::Texto()
  : ObjetoGraficoRectangular() {
  this->size = SIZE;
  this->tipoFuente = LETRA;
}

Texto::~Texto() {

}

void Texto::agregarAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::agregarAtributos(nodo);

  XmlNodo nodoSize("size");
  nodoSize.setContenido(this->size);
  nodo->agregarHijo(nodoSize);

  XmlNodo nodoTipoFuente("tipoFuente");
  nodoTipoFuente.setContenido(this->tipoFuente);
  nodo->agregarHijo(nodoTipoFuente);

}

void Texto::obtenerAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::obtenerAtributos(nodo);

  this->size = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->tipoFuente = nodo->getContenido();
  *nodo = nodo->getHermano();

}

int Texto::getSize() const {
  return size;
}

void Texto::setSize( int size ) {
  this->size = size;

}

std::string Texto::getTipoFuente() const {
  return tipoFuente;
}

void Texto::setTipoFuente(const std::string& fuente) {
  tipoFuente = fuente;
}

std::string Texto::toString() const {
  return "";
}

int Texto::getId() const {
  return COD_ERROR;
}
