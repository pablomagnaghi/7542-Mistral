#ifndef _FIGURA_TEXTO_FIJO_H_INCLUDED_
#define _FIGURA_TEXTO_FIJO_H_INCLUDED_

#include "TextoFijoGui.h"
#include "ObjetoGui.h"

#include "FiguraRectangular.h"

#include "Comportamiento.h"

class MyArea;

class FiguraTextoFijo : public FiguraRectangular {
private:
  TextoFijoGui* txtGui;

public:
  FiguraTextoFijo( TextoFijoGui*, MyArea* );
  virtual FiguraRectangular* clone( ObjetoGuiRectangular* );
  virtual void draw();	
  virtual ObjetoGui* getObjetoGui();
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y  );

};

#endif
