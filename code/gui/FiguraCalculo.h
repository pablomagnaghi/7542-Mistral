#ifndef _FIGURA_CALCULO_VARIABLE_H_INCLUDED_
#define _FIGURA_CALCULO_VARIABLE_H_INCLUDED_

#include "CalculoGui.h"
#include "ObjetoGui.h"
#include "FiguraRectangular.h"

#include "Comportamiento.h"
#include <gtkmm.h>
class MyArea;

class FiguraCalculo : public FiguraRectangular {
private:
  CalculoGui* calculoGui;

public:
  FiguraCalculo( CalculoGui*, MyArea* );
  virtual FiguraRectangular* clone( ObjetoGuiRectangular* );
  virtual void draw();	
  virtual ObjetoGui* getObjetoGui();
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y );

};

#endif
