#include "ListaGui.h"

#include "Comportamiento.h"
#include "./../ObjetoLista.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>
#include "./../ObjetoGraficoRectangular.h"

ListaGui::ListaGui( ObjetoLista& l ) 
: ObjetoGuiRectangular( &l), lista(l) {
}

ObjetoGuiRectangular* ListaGui::clone(ObjetoGraficoRectangular* listaModelo) {
  ListaGui* listaG = new ListaGui( *(ObjetoLista*)listaModelo );
  return listaG;
}

ObjetoLista* ListaGui::getLista() {
  return &lista;
}


void ListaGui::setAttr( const std::string& nombre, const std::string& valor ) {
  if ( nombre == "xpathItem" )
    lista.setXpath( valor );
  else
    ObjetoGui::setAttr( nombre, valor );

  this->notifyObservadores();
}

void ListaGui::getAttr( const std::string& nombre, std::string& valor ) {
  if ( nombre == "xpathItem" )
    valor = lista.getXpath();
  else
    ObjetoGui::getAttr( nombre, valor );
}

void ListaGui::setAttr( const std::string& nombre, const int valor ) {
  if ( nombre == "size" )
    lista.setSize( valor );
  else
    ObjetoGuiRectangular::setAttr( nombre, valor );
  this->notifyObservadores();
}

void ListaGui::getAttr( const std::string& nombre, int& valor ) {
  if ( nombre == "size" )
    valor = lista.getSize();
  else
    ObjetoGuiRectangular::getAttr( nombre, valor );
}

void ListaGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    ObjetoGuiRectangular::getAtributos(listaDeAtributos);
    FormatoAtributo f1( "xpathItem", ATTR_STRING );
    FormatoAtributo f2( "size", ATTR_INT);

    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
  }

