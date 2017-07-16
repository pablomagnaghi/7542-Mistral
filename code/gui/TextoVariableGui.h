#ifndef _TEXTO_VARIABLE_GUI_H_INCLUDED_
#define _TEXTO_VARIABLE_GUI_H_INCLUDED_

#include <gtkmm.h>
#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"
#include "./../TextoVariable.h"
#include "./../ObjetoGraficoRectangular.h"

#include <string>

class TextoVariableGui : public ObjetoGuiRectangular {
private:
	TextoVariable& textoModelo;
	
public:
  TextoVariableGui( TextoVariable& );
  ObjetoGuiRectangular* clone(ObjetoGraficoRectangular*);

  std::string getTextoXpath() const;
  void setTextoXpath( const std::string& );

  void getAttr( const std::string& nombre, std::string& valor );
  void setAttr( const std::string& nombre, const std::string& valor );
  void setAttr( const std::string& nombre, const int valor );
  void getAttr( const std::string& nombre, int& valor );

  void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );

};
#endif