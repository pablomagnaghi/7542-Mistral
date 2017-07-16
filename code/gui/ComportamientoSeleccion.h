#ifndef _COMPORTAMIENTO_SELECCION_H_INCLUDED_
#define _COMPORTAMIENTO_SELECCION_H_INCLUDED_

#include "Comportamiento.h"
#include <gtkmm.h>
#include "MyArea.h"

#include "Figura.h"
#include "TablaDePropiedades.h"

class MyArea;

/*
 * Implamentado con patron prototype para cualquier figura y su
 * correspondiente objeto gui que hereden de FiguraRectangular y
 * ObjetoGuiRectangular respectivamente.
 **/

class ComportamientoSeleccion : public Comportamiento {
private:
  MyArea* area;

  Figura* objActual;
  Comportamiento* compActual;
  TablaDePropiedades& tablaDePropiedades;

  bool doubleClick;
  void cargarObjYComportamiento( int x, int y );
public:
  ComportamientoSeleccion( MyArea*, TablaDePropiedades&  );
  bool on_button_press_event (GdkEventButton* event);
  bool on_button_release_event (GdkEventButton* event);
  bool on_motion_notify_event (GdkEventMotion* event );
  bool on_key_press_event ( GdkEventKey* event );

  void clear();
  void seleccionar( Figura* figura );
  void removeActual();
};

#endif
