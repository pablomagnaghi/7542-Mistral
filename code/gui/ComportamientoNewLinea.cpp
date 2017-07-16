#include "ComportamientoNewLinea.h"

#include "Comportamiento.h"
#include <gtkmm.h>
#include "MyArea.h"

#include "./../Linea.h"
#include "LineaGui.h"
#include "FiguraLinea.h"

#include <iostream>

ComportamientoNewLinea::ComportamientoNewLinea( MyArea* area, TablaDePropiedades& tabla )
: area(area), tabla(tabla) {
  l = NULL;
}

bool ComportamientoNewLinea::on_button_press_event (GdkEventButton* event) { 
  if ( !l ) {
    Linea* lineaModelo = new Linea( event->x, event->y );
    l = new LineaGui( *lineaModelo );
    l->setX( event->x );
    l->setY( event->y );
    FiguraLinea* f = new FiguraLinea( l, this->area );
    area->getHoja()->agregarObjeto( lineaModelo );
    area->addObjetoGui( l );
    area->addFigura( f );
  }
  return true;
}

bool ComportamientoNewLinea::on_button_release_event (GdkEventButton* event) {
  if ( l ) {
    tabla.setObjeto( l );
    l = NULL;
    area->setComportamientoSeleccion();
  }
  return true;
}

bool ComportamientoNewLinea::on_motion_notify_event (GdkEventMotion* event) {
  if ( l ) {
    l->setXFinal( event->x );
    l->setYFinal( event->y );
  }
  return true;
}

