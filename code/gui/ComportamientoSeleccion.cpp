#include "ComportamientoSeleccion.h"

#include "Comportamiento.h"
#include <gtkmm.h>
#include "MyArea.h"
#include "TablaDePropiedades.h"

#include "Figura.h"
#include "ObjetoGui.h"

#include <iostream>
#include <gdk/gdkkeysyms.h>

ComportamientoSeleccion::ComportamientoSeleccion( MyArea* area, TablaDePropiedades& t )
: area(area), tablaDePropiedades(t) {
  objActual = NULL;
  compActual = NULL;
  doubleClick = false;
}

bool ComportamientoSeleccion::on_button_press_event (GdkEventButton* event) {
  doubleClick = false;

  cargarObjYComportamiento( event->x, event->y );
  if ( compActual ) {
    compActual->on_button_press_event( event );
    this->tablaDePropiedades.setObjeto( objActual->getObjetoGui() );
  
    if ( (event->button == 1 ) && (event->type == GDK_2BUTTON_PRESS ) )
      doubleClick = true;
  }
  return true;
}

bool ComportamientoSeleccion::on_button_release_event (GdkEventButton* event) {
  cargarObjYComportamiento( event->x, event->y );
  if ( compActual )
    compActual->on_button_release_event( event );

 if ( doubleClick ) {
    Gtk::Window* w = objActual->getWindowParaConfigurar( event->x, event->y );
    if ( w ) {
      Gtk::Main::run( *w );
      delete w;
      doubleClick = false;
    }
  }

  return true;
}

bool ComportamientoSeleccion::on_motion_notify_event (GdkEventMotion* event) {

  //cargarObjYComportamiento( event->x, event->y );
  if ( (compActual) && (!doubleClick) )
    compActual->on_motion_notify_event( event );
  return true;
}

void ComportamientoSeleccion::seleccionar( Figura* figura ) {
  if ( objActual )
      objActual->setSeleccionada( false );

  objActual = figura;
    if ( objActual ) {
      compActual = objActual->getComportamiento();
      objActual->setSeleccionada( true );
    this->tablaDePropiedades.setObjeto( objActual->getObjetoGui() );

    }
    else {
      objActual = NULL;
      compActual = NULL;
    }
    doubleClick = false;

}

bool ComportamientoSeleccion::on_key_press_event ( GdkEventKey* event ) {
  std::cout << std::endl <<"CHAU";
  if ( event->type == GDK_KEY_RELEASE ) {
    if ( event->keyval == GDK_Delete ) {
      if ( objActual ) {
	area->removeObjetoGui( objActual->getObjetoGui() );
	area->removeFigura( objActual );
      }
    }
  }
  
  return true;
}

void ComportamientoSeleccion::cargarObjYComportamiento( int x, int y ) {
  if ( (!objActual) || (!objActual->pertenece(x,y)) ) {
    if ( objActual )
      objActual->setSeleccionada( false );
    objActual = area->seleccionar( x, y );
    if ( objActual ) {
      compActual = objActual->getComportamiento();
      objActual->setSeleccionada( true );
    }
    else {
      objActual = NULL;
      compActual = NULL;
    }
    doubleClick = false;
  }
}

void ComportamientoSeleccion::removeActual() {
  if ( objActual ) {
    Figura* figuraAEliminar = objActual;
    ObjetoGui* objAEliminar = figuraAEliminar->getObjetoGui();
    ObjetoGrafico* objGraficoAEliminar = objAEliminar->getObjetoGrafico();
    this->clear();

    area->removeFigura( figuraAEliminar );
    area->removeObjetoGui( objAEliminar );
    area->getHoja()->removeObjeto( objGraficoAEliminar );

    delete figuraAEliminar;
    delete objAEliminar;
    delete objGraficoAEliminar;

    area->drawAll();
  }
}

void ComportamientoSeleccion::clear() {
  this->objActual = NULL;
  this->compActual = NULL;
  this->tablaDePropiedades.setObjeto( NULL );
}

