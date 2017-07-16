#ifndef _TEXTO_FIJO_GUI_H_INCLUDED_
#define _TEXTO_FIJO_GUI_H_INCLUDED_

#include <gtkmm.h>
#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"
#include "./../TextoFijo.h"
#include <string>
#include "./../ObjetoGraficoRectangular.h"

class TextoFijoGui : public ObjetoGuiRectangular {
private:
  TextoFijo& textoModelo;
	
public:
	TextoFijoGui( TextoFijo& );
	ObjetoGuiRectangular* clone(ObjetoGraficoRectangular*);

	std::string getTexto() const;
      	void setTexto( const std::string& );

  void getAttr( const std::string& nombre, std::string& valor );
  void setAttr( const std::string& nombre, const std::string& valor );
  void setAttr( const std::string& nombre, const int valor );
  void getAttr( const std::string& nombre, int& valor );

  void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );
};
#endif