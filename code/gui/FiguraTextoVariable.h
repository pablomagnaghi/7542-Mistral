#ifndef _FIGURA_TEXTO_VARIABLE_H_INCLUDED_
#define _FIGURA_TEXTO_VARIABLE_H_INCLUDED_

#include "TextoVariableGui.h"
#include "ObjetoGui.h"
#include "FiguraRectangular.h"

#include "Comportamiento.h"

class MyArea;

class FiguraTextoVariable : public FiguraRectangular {
private:
  TextoVariableGui* txtGui;

public:
  FiguraTextoVariable( TextoVariableGui*, MyArea* );
  virtual FiguraRectangular* clone( ObjetoGuiRectangular* );
  virtual void draw();	
  virtual ObjetoGui* getObjetoGui();
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y  );

};

#endif
