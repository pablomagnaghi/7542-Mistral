#include "ComportamientoLinea.h"

#include "LineaGui.h"
#include <iostream>

ComportamientoLinea::ComportamientoLinea( LineaGui& l )
: linea(l) {
  desdeInicio = desdeFinal = dragAndDrop = false;
}

bool ComportamientoLinea::on_button_press_event (GdkEventButton* event ) {
  desdeInicio = desdeFinal = dragAndDrop = false;

  if ( Comportamiento::cercano(event->x,event->y, linea.getX(), linea.getY() ) ) {
    desdeInicio = true;
  }
  else if ( Comportamiento::cercano( event->x,event->y, linea.getXFinal(),
				     linea.getYFinal() ) ) {
    desdeFinal = true;
  }
  else {
    deltaXi = event->x - linea.getX();
    deltaYi = event->y - linea.getY();

    deltaXf = event->x - linea.getXFinal();
    deltaYf = event->y - linea.getYFinal();

    dragAndDrop = true;
  }

  return true;
}

bool ComportamientoLinea::on_button_release_event (GdkEventButton* event ) {
  desdeInicio = desdeFinal = dragAndDrop = false;
  return true;
}

bool ComportamientoLinea::on_motion_notify_event (GdkEventMotion* event ) {
  if ( desdeInicio ) {
    linea.setX( event->x );
    linea.setY( event->y );
  }
  if ( desdeFinal ) {
    linea.setXFinal( event->x );
    linea.setYFinal( event->y );
  }
  if ( dragAndDrop ) {
    linea.setX( event->x - deltaXi );
    linea.setY( event->y - deltaYi );
    linea.setXFinal( event->x - deltaXf );
    linea.setYFinal( event->y - deltaYf );
  }
  return true;
}

