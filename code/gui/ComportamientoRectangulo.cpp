#include "ComportamientoRectangulo.h"

#include "Comportamiento.h"

#include "ObjetoGuiRectangular.h"

#include <iostream>

ComportamientoRectangulo::ComportamientoRectangulo( ObjetoGuiRectangular* obj )
: obj(obj) {
  dragAndDrop = resize = false;
}

bool ComportamientoRectangulo::on_button_press_event (GdkEventButton* event ) {
  dragAndDrop = resize = false;
  if ( Comportamiento::cercano( event->x, 
				event->y, 
				obj->getX() + obj->getAncho(), 
				obj->getY() + obj->getAlto() ) ) {
    resize = true;
  }	else {
    dragAndDrop = true;
    deltaX = event->x - obj->getX();
    deltaY = event->y - obj->getY();
  }

  return true;
}

bool ComportamientoRectangulo::on_button_release_event (GdkEventButton* event ) {
  dragAndDrop = resize = false;
  return true;
}

bool ComportamientoRectangulo::on_motion_notify_event (GdkEventMotion* event ) {
  if ( dragAndDrop ) {
    obj->setX( event->x - deltaX );
    obj->setY( event->y - deltaY );
  }
  if ( resize ) {
    obj->setAncho( event->x - obj->getX()  );
    obj->setAlto( event->y - obj->getY() );
  }
  return true;
}


