#include "CalculoGui.h"

#include "Comportamiento.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>
#include "./../ObjetoGraficoRectangular.h"

CalculoGui::CalculoGui( Calculo& c ) 
: ObjetoGuiRectangular(&c), calculo(c) {
}

ObjetoGuiRectangular* CalculoGui::clone(ObjetoGraficoRectangular* objModelo) {
  CalculoGui* txt = new CalculoGui( *(Calculo*)objModelo );
  return txt;
}

Calculo* CalculoGui::getCalculo() {
  return &this->calculo;
}

void CalculoGui::setAttr( const std::string& nombre, const int valor ) {
  if ( nombre == "size" )
    calculo.setSize( valor );
  else
    ObjetoGuiRectangular::setAttr( nombre, valor );
  this->notifyObservadores();
}

void CalculoGui::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "size" )
    valor = calculo.getSize();
  else
    ObjetoGuiRectangular::getAttr( nombre, valor );
}

void CalculoGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGuiRectangular::getAtributos(listaDeAtributos);
    FormatoAtributo f2( "size", ATTR_INT);

    listaDeAtributos.push_back( f2 );
  }


