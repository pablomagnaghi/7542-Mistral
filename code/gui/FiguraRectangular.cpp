#include "FiguraRectangular.h"

#include "Figura.h"
#include "ObjetoGuiRectangular.h"

#include "Comportamiento.h"
#include "ComportamientoRectangulo.h"
#include "MyArea.h"

FiguraRectangular::FiguraRectangular( ObjetoGuiRectangular* objGui, 
				      MyArea* area ) 
: Figura( area ), r (objGui) {
  objGui->agregarObservador( this );
}

// FiguraRectangular* FiguraRectangular::clone(ObjetoGuiRectangular* o) {
//   return new FiguraRectangular( o, this->getArea() );
// }

void FiguraRectangular::draw() {
  if ( seleccionada ) {
    MyArea* area = getArea();
    Glib::RefPtr<Gdk::Window> window = area->get_window();
    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

    cr->set_line_width(2.0);
    cr->set_source_rgb(0.8, 0.5, 0.0);
    cr->rectangle( r->getX()-6, r->getY()-6, r->getAncho()+12, r->getAlto()+12 );
    cr->stroke();
  }
}

bool FiguraRectangular::pertenece( int x, int y ) const {
  bool result = true;
  result = ( (x>=r->getX()) && (x<=r->getX()+r->getAncho()) );
  if ( result )
    result = ( (y>=r->getY()) && (y<=r->getY()+r->getAlto()) );
  return result;
}

Comportamiento* FiguraRectangular::getComportamiento() {
  return new ComportamientoRectangulo( this->r );
}

Comportamiento* FiguraRectangular::getComportamientoSeleccion() {
  return NULL;
}

