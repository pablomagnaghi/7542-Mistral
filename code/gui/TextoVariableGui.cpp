#include "TextoVariableGui.h"

#include "Comportamiento.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>

TextoVariableGui::TextoVariableGui( TextoVariable& txt ) 
: ObjetoGuiRectangular( &txt ), textoModelo(txt) {
}

ObjetoGuiRectangular* TextoVariableGui::clone(ObjetoGraficoRectangular* otroTexto) {
  TextoVariableGui* txt = new TextoVariableGui( *(TextoVariable*)otroTexto );
  textoModelo.setTextoXpath( this->getTextoXpath() );
  return txt;
}


std::string TextoVariableGui::getTextoXpath() const {
  return this->textoModelo.getTextoXpath();
}

void TextoVariableGui::setTextoXpath( const std::string& txt ) {
  this->textoModelo.setTextoXpath( txt );
}


void TextoVariableGui::setAttr( const std::string& nombre, const std::string& valor ) {
  if ( nombre == "textoXpath" )
    textoModelo.setTextoXpath( valor );
  else
    ObjetoGui::setAttr( nombre, valor );

  this->notifyObservadores();
}

void TextoVariableGui::getAttr( const std::string& nombre, std::string& valor ) {
  if ( nombre == "textoXpath" )
    valor = textoModelo.getTextoXpath();
  else
    ObjetoGui::getAttr( nombre, valor );
}

void TextoVariableGui::setAttr( const std::string& nombre, const int valor ) {
  if ( nombre == "size" )
    textoModelo.setSize( valor );
  else
    ObjetoGuiRectangular::setAttr( nombre, valor );
  this->notifyObservadores();
}

void TextoVariableGui::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "size" )
    valor = textoModelo.getSize();
  else
    ObjetoGuiRectangular::getAttr( nombre, valor );
}

void TextoVariableGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGuiRectangular::getAtributos(listaDeAtributos);
    FormatoAtributo f1( "textoXpath", ATTR_STRING );
    FormatoAtributo f2( "size", ATTR_INT);

    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
  }

