#ifndef _LINEA_GUI_H_INCLUDED_
#define _LINEA_GUI_H_INCLUDED_

#include "ObjetoGui.h"
#include "./../Linea.h"

class LineaGui : public ObjetoGui {
private:
  Linea& lineaModelo;

public:
  LineaGui( Linea& lineaModelo );

  int getXFinal() const;
  int getYFinal() const;

  void setXFinal( int );
  void setYFinal( int );

  virtual void setAttr( const std::string& nombre, const int valor );
  virtual void getAttr( const std::string& nombre, int& valor );
  virtual void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );

};
#endif