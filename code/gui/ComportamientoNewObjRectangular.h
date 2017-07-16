#ifndef _COMPORTAMIENTO_NEW_OBJ_RECTANGULAR_H_INCLUDED_
#define _COMPORTAMIENTO_NEW_OBJ_RECTANGULAR_H_INCLUDED_

#include "Comportamiento.h"
#include <gtkmm.h>
#include "MyArea.h"

#include "ObjetoGuiRectangular.h"
#include "FiguraRectangular.h"
#include "./../ObjetoGraficoRectangular.h"
#include "TablaDePropiedades.h"

class MyArea;

/*
 * Implamentado con patron prototype para cualquier figura y su
 * correspondiente objeto gui que hereden de FiguraRectangular y
 * ObjetoGuiRectangular respectivamente.
 **/

class ComportamientoNewObjetoRectangular : public Comportamiento {
private:
  ObjetoGraficoRectangular* modeloPrototype;
  FiguraRectangular* fPrototype;
  ObjetoGuiRectangular* objPrototype;

  ObjetoGraficoRectangular* modeloCreado;
  FiguraRectangular* figuraCreada;
  ObjetoGuiRectangular* objetoGuiCreado;

  MyArea* area;
  TablaDePropiedades& tabla;

public:
  ComportamientoNewObjetoRectangular( MyArea*,FiguraRectangular*,
				      ObjetoGuiRectangular*,
				      ObjetoGraficoRectangular*,
				      TablaDePropiedades& );
  bool on_button_press_event (GdkEventButton* event);
  bool on_button_release_event (GdkEventButton* event);
  bool on_motion_notify_event (GdkEventMotion* event );
};

#endif
