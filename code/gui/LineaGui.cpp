#include "LineaGui.h"

#include "./../Linea.h"

LineaGui::LineaGui( Linea& lineaModelo )
: ObjetoGui( &lineaModelo ), lineaModelo(lineaModelo) {
}

int LineaGui::getXFinal() const {
  return lineaModelo.getPosXfinal();
}

int LineaGui::getYFinal() const {
  return MAXALTO - lineaModelo.getPosYfinal();
}


void LineaGui::setXFinal( int x ) {
  lineaModelo.setPosXfinal( x );
  this->notifyObservadores();
}

void LineaGui::setYFinal( int y ) {
  lineaModelo.setPosYfinal( MAXALTO - y );
  this->notifyObservadores();
}

void LineaGui::setAttr( const std::string& nombre, int valor ) {
  if ( nombre == "posXfinal" )
    this->setXFinal( valor );
  else if ( nombre == "posYfinal" )
    this->setYFinal( valor );
  else
    ObjetoGui::setAttr( nombre, valor );

  this->notifyObservadores();
}

void LineaGui::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "posXfinal" )
    valor = this->getXFinal( );
  else if ( nombre == "posYfinal" )
    valor = this->getYFinal( );
  else
    ObjetoGui::getAttr( nombre, valor );
}


void LineaGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGui::getAtributos(listaDeAtributos);
    FormatoAtributo f1( "posXfinal", ATTR_INT );
    FormatoAtributo f2( "posYfinal", ATTR_INT );
 
    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
  }
