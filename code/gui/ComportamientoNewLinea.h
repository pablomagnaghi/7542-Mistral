#ifndef _COMPORTAMIENTO_NEW_LINEA_H_INCLUDED_
#define _COMPORTAMIENTO_NEW_LINEA_H_INCLUDED_

#include "Comportamiento.h"
#include <gtkmm.h>
#include "LineaGui.h"
#include "MyArea.h"
#include "TablaDePropiedades.h"

class MyArea;

class ComportamientoNewLinea : public Comportamiento {
private:
  LineaGui* l;
  MyArea* area;
  TablaDePropiedades& tabla;
public:
  ComportamientoNewLinea( MyArea*, TablaDePropiedades& tabla );
  bool on_button_press_event (GdkEventButton* event);
  bool on_button_release_event (GdkEventButton* event);
  bool on_motion_notify_event (GdkEventMotion* event );
};

#endif
