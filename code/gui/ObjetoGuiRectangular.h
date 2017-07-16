#ifndef _OBJETO_GUI_RECTANGULAR_H_INCLUDED_
#define _OBJETO_GUI_RECTANGULAR_H_INCLUDED_

#include "ObjetoGui.h"
#include "./../ObjetoGraficoRectangular.h"

class ObjetoGuiRectangular : public ObjetoGui {
private:
  ObjetoGraficoRectangular* objModelo;

public:

  ObjetoGuiRectangular( ObjetoGraficoRectangular* );
  virtual ObjetoGuiRectangular* clone( ObjetoGraficoRectangular*) = 0;
  
  ObjetoGraficoRectangular* getObjetoGrafico();
  int getAncho() const;
  int getAlto() const;
  virtual void setAncho( int x );
  void setAlto( int y );

  void getAttr( const std::string& nombre, int& valor );
  void setAttr( const std::string& nombre, int valor );
  void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );

  virtual int getY() const;
  virtual void setY( int y );

};

#endif