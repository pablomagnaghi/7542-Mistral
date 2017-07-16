#include "ComportamientoNewObjRectangular.h"

#include "Comportamiento.h"
#include <gtkmm.h>
#include "MyArea.h"

#include "ObjetoGuiRectangular.h"
#include "FiguraRectangular.h"
#include "./../ObjetoGraficoRectangular.h"

#include <iostream>

ComportamientoNewObjetoRectangular::
ComportamientoNewObjetoRectangular( MyArea* area,FiguraRectangular* f,  
				    ObjetoGuiRectangular* o,
				    ObjetoGraficoRectangular* m,
				    TablaDePropiedades& tabla )
: area(area), fPrototype(f), objPrototype(o), modeloPrototype(m), tabla(tabla) {
  figuraCreada = NULL;
  objetoGuiCreado = NULL;
}

bool ComportamientoNewObjetoRectangular::on_button_press_event (GdkEventButton* event) { 
  if ( (!figuraCreada) && (!objetoGuiCreado) ) {
    modeloCreado = modeloPrototype->clone();

     objetoGuiCreado = objPrototype->clone( modeloCreado );
     objetoGuiCreado->setX( event->x );
     objetoGuiCreado->setY( event->y );
     objetoGuiCreado->setAncho( 10 );
     objetoGuiCreado->setAlto( 10 );

     figuraCreada = fPrototype->clone( objetoGuiCreado );
            area->getHoja()->agregarObjeto( modeloCreado );
     area->addObjetoGui( objetoGuiCreado );
     area->addFigura( figuraCreada );
  }
  return true;
}

bool ComportamientoNewObjetoRectangular::on_button_release_event (GdkEventButton* event) {
  if ( (figuraCreada) && (objetoGuiCreado) ) {




    area->setComportamientoSeleccion(false,figuraCreada);

    //tabla.setObjeto( objetoGuiCreado );
    figuraCreada = NULL;
    objetoGuiCreado = NULL;
  }
  return true;
}

bool ComportamientoNewObjetoRectangular::on_motion_notify_event (GdkEventMotion* event) {
  if ( (figuraCreada) && (objetoGuiCreado) ) {
    objetoGuiCreado->setAncho( event->x - objetoGuiCreado->getX()  );
    objetoGuiCreado->setAlto( event->y - objetoGuiCreado->getY() );
  }
  return true;
}

