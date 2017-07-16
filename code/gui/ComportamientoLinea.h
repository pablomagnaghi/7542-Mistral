#ifndef _COMPORTAMIENTO_LINEA_H_INCLUDED_
#define _COMPORTAMIENTO_LINEA_H_INCLUDED_

#include "Comportamiento.h"

#include "LineaGui.h"

class ComportamientoLinea : public Comportamiento {
private:
  LineaGui& linea;
  int deltaXi;
  int deltaYi;
  int deltaXf;
  int deltaYf;
  bool desdeInicio;
  bool desdeFinal;
  bool dragAndDrop;

public:
  ComportamientoLinea( LineaGui& );
  bool on_button_press_event (GdkEventButton* event );
  bool on_button_release_event (GdkEventButton* event );
  bool on_motion_notify_event (GdkEventMotion* event );
};

#endif
