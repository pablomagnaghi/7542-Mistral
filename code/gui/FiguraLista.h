#ifndef _FIGURA_LISTA_VARIABLE_H_INCLUDED_
#define _FIGURA_LISTA_VARIABLE_H_INCLUDED_

#include "ListaGui.h"
#include "ObjetoGui.h"
#include "FiguraRectangular.h"
#include "./../Columna.h"

#include "Comportamiento.h"

class MyArea;

enum t_posCulmna {
		    COL_IZQUIERDA = 0,
		    COL_CENTRO,
		    COL_DERECHA
		  };
typedef enum t_posCulmna tPosColumna;

class FiguraLista : public FiguraRectangular {
private:
  ListaGui* listaGui;

  void dibujarColumna( Columna*, int& posXActual, int& posYActual, Cairo::RefPtr<Cairo::Context> );

  void dibujarTexto( int posX, int posY, Texto*, Cairo::RefPtr<Cairo::Context> cr  );
public:
  FiguraLista( ListaGui*, MyArea* );
  virtual FiguraRectangular* clone( ObjetoGuiRectangular* );
  virtual void draw();	
  virtual ObjetoGui* getObjetoGui();
  virtual Gtk::Window* getWindowParaConfigurar( int x , int y  );
  virtual Comportamiento* getComportamiento();


  void getTipoPocision( int x, int y, int& numColumna, Columna** col,
			Texto** txt, tPosColumna& posCol, tipoCelda& tipoCelda );
};

#endif
