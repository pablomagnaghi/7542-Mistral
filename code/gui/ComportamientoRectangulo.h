#ifndef _COMPORTAMIENTO_RECTANGULO_H_INCLUDED_
#define _COMPORTAMIENTO_RECTANGULO_H_INCLUDED_

#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"

#define DISTANCIA_RESIZE	20

enum t_posTo {
		DRAG_AND_DROP,
		RESIZE_IZQUIERDA,
		RESIZE_DERECHA,
		RESIZE_ARRIBA,
		RESIZE_ABAJO,
		RESIZE_ARRIBA_IZQUIERDA,
		RESIZE_ARRIBA_DERECHA,
		RESIZE_ABAJO_DERECHA,
		RESIZE_ABAJO_IZQUIERDA };

typedef enum t_posTo tipoPosTo;

class ComportamientoRectangulo : public Comportamiento {
private:
  ObjetoGuiRectangular* obj;
  bool dragAndDrop;
  bool resize;

  int deltaX;
  int deltaY;

public:
  ComportamientoRectangulo( ObjetoGuiRectangular* );
  bool on_button_press_event (GdkEventButton* event );
  bool on_button_release_event (GdkEventButton* event );
  bool on_motion_notify_event (GdkEventMotion* event );
};

#endif
