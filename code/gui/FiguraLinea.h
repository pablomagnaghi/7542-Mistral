#ifndef _FIGURA_LINEA_H_INCLUDED_
#define _FIGURA_LINEA_H_INCLUDED_

#include "Figura.h"
#include "MyArea.h"
#include "Comportamiento.h"
#include "ObjetoGui.h"

#define MIN_SEL_LINEA	10

class LineaGui;

class FiguraLinea : public Figura {
private:
  LineaGui* l;

public:
  FiguraLinea( LineaGui*, MyArea* );
  void draw();	
  bool pertenece( int x, int y ) const;
  Comportamiento* getComportamiento();
  Comportamiento* getComportamientoSeleccion();
  ObjetoGui* getObjetoGui();
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y  );

};

#endif
