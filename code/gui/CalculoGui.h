#ifndef _CALCULO_GUI_H_INCLUDED_
#define _CALCULO_GUI_H_INCLUDED_

#include <gtkmm.h>
#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"
#include "./../Calculo.h"
#include "./../ObjetoGraficoRectangular.h"

#include <string>

class CalculoGui : public ObjetoGuiRectangular {
private:
  Calculo& calculo;
	
public:
	CalculoGui( Calculo& );
	ObjetoGuiRectangular* clone(ObjetoGraficoRectangular*);

	Calculo* getCalculo();
	std::string getTitulo() const;
      	void setTitulo( const std::string& );

	void setAttr( const std::string& nombre, const int valor );
	void getAttr( const std::string& nombre, int& valor );
	void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );

};
#endif