#include "ObjetoGuiRectangular.h"

#include "ObjetoGui.h"
#include "./../Constantes.h"

#include <iostream>

ObjetoGuiRectangular::ObjetoGuiRectangular( ObjetoGraficoRectangular* obj )
: ObjetoGui( obj ), objModelo(obj) {
}

ObjetoGraficoRectangular* ObjetoGuiRectangular::getObjetoGrafico() {
  return this->objModelo;
}


int ObjetoGuiRectangular::getAncho() const {
  return objModelo->getAncho();
}

int ObjetoGuiRectangular::getAlto() const {
  return  objModelo->getAlto();
}

void ObjetoGuiRectangular::setAncho( int ancho ) {
  objModelo->setAncho( ancho );
  this->notifyObservadores();
}

void ObjetoGuiRectangular::setAlto( int alto ) {
  objModelo->setPosY( objModelo->getPosY() + objModelo->getAlto() - alto );
  objModelo->setAlto( alto );
  this->notifyObservadores();
}

int ObjetoGuiRectangular::getY() const {
  return ( MAXALTO - objModelo->getPosY() - this->getAlto() );
}

void ObjetoGuiRectangular::setY( int y ) {
  objModelo->setPosY( MAXALTO -  this->getAlto() - y );
}

void ObjetoGuiRectangular::setAttr( const std::string& nombre, int valor ) {
  if ( nombre == "ancho" )
    this->setAncho( valor );
  else if ( nombre == "alto" )
    this->setAlto( valor );
  else
    ObjetoGui::setAttr( nombre, valor );

  this->notifyObservadores();
}

void ObjetoGuiRectangular::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "ancho" )
    valor = this->getAncho();
  else if ( nombre == "alto" )
    valor = this->getAlto();
  else
    ObjetoGui::getAttr( nombre, valor );
}


void ObjetoGuiRectangular::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGui::getAtributos(listaDeAtributos);
    FormatoAtributo f1( "ancho", ATTR_INT );
    FormatoAtributo f2( "alto", ATTR_INT );
 
    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
  }
