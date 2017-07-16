#ifndef _FIGURA_RECTANGULAR_H_INCLUDED_
#define _FIGURA_RECTANGULAR_H_INCLUDED_

#include "Figura.h"
#include "ObjetoGuiRectangular.h"

#include "Comportamiento.h"
#include <gtkmm.h>

class MyArea;

class FiguraRectangular : public Figura {
private:
  ObjetoGuiRectangular* r;

public:
  FiguraRectangular( ObjetoGuiRectangular*, MyArea* );
  virtual FiguraRectangular* clone( ObjetoGuiRectangular* ) = 0;
  virtual Gtk::Window* getWindowParaConfigurar( int x, int y ) = 0;
  virtual void draw();	
  bool pertenece( int x, int y ) const;
  Comportamiento* getComportamiento();
  Comportamiento* getComportamientoSeleccion();

  virtual ~FiguraRectangular() {
  }
};

#endif
