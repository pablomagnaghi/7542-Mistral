#ifndef _FIGURA_H_INCLUDED_
#define _FIGURA_H_INCLUDED_

#include "Observador.h"
#include "Comportamiento.h"
#include "ObjetoGui.h"
#include <gtkmm.h>

//#include "MyArea.h"

class MyArea;

class Figura : public Observador {

private:
  MyArea* area;
protected:
  bool seleccionada;

public:

  Figura(  MyArea* unArea );
  MyArea* getArea();

  virtual void notify();

  virtual void draw() = 0;	
  virtual bool pertenece( int x, int y ) const = 0;
  virtual Comportamiento* getComportamiento() = 0;
  virtual Comportamiento* getComportamientoSeleccion() = 0;
  virtual ObjetoGui* getObjetoGui() = 0;
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y ) = 0;

  void setSeleccionada( bool seleccionada = true ) {
    this->seleccionada = seleccionada;
  }

  virtual ~Figura() {
  }
};

#endif 