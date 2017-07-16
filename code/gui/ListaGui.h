#ifndef _LISTA_GUI_H_INCLUDED_
#define _LISTA_GUI_H_INCLUDED_

#include <gtkmm.h>
#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"
#include "./../ObjetoLista.h"
#include "./../ObjetoGraficoRectangular.h"

#include <string>

class ListaGui : public ObjetoGuiRectangular {
private:
  ObjetoLista& lista;
	
public:
	ListaGui( ObjetoLista& );
	ObjetoGuiRectangular* clone( ObjetoGraficoRectangular* );
	ObjetoLista* getLista();


  void getAttr( const std::string& nombre, std::string& valor );
  void setAttr( const std::string& nombre, const std::string& valor );
  void setAttr( const std::string& nombre, const int valor );
  void getAttr( const std::string& nombre, int& valor );

  void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );
};
#endif