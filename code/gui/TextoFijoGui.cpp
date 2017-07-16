#include "TextoFijoGui.h"

#include "Comportamiento.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>
#include "./../ObjetoGraficoRectangular.h"

TextoFijoGui::TextoFijoGui( TextoFijo& txt ) 
: ObjetoGuiRectangular( &txt ), textoModelo(txt) {
}

ObjetoGuiRectangular* TextoFijoGui::clone(ObjetoGraficoRectangular* otroTexto) {
  TextoFijoGui* texto = new TextoFijoGui( *(TextoFijo*)otroTexto );
  texto->setTexto( getTexto() );
  return texto;
}


std::string TextoFijoGui::getTexto() const {
  return this->textoModelo.getTexto();
}

void TextoFijoGui::setTexto( const std::string& txt ) {
  this->textoModelo.setTexto( txt );
}


void TextoFijoGui::setAttr( const std::string& nombre, const std::string& valor ) {
  if ( nombre == "texto" )
    textoModelo.setTexto( valor );
  else
    ObjetoGui::setAttr( nombre, valor );

  this->notifyObservadores();
}

void TextoFijoGui::getAttr( const std::string& nombre, std::string& valor ) {
  if ( nombre == "texto" )
    valor = textoModelo.getTexto();
  else
    ObjetoGui::getAttr( nombre, valor );
}

void TextoFijoGui::setAttr( const std::string& nombre, const int valor ) {
  if ( nombre == "size" )
    textoModelo.setSize( valor );
  else
    ObjetoGuiRectangular::setAttr( nombre, valor );
  this->notifyObservadores();
}

void TextoFijoGui::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "size" )
    valor = textoModelo.getSize();
  else
    ObjetoGuiRectangular::getAttr( nombre, valor );
}

void TextoFijoGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGuiRectangular::getAtributos(listaDeAtributos);
    FormatoAtributo f1( "texto", ATTR_STRING );
    FormatoAtributo f2( "size", ATTR_INT);

    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
  }

