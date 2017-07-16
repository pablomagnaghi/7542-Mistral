#include "FiguraLinea.h"

#include "LineaGui.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>
#include <math.h>
#include "Color.h"
#include "ObjetoGui.h"

#include "ComportamientoLinea.h"
#include <iostream>


FiguraLinea::FiguraLinea( LineaGui* l, MyArea* unArea ) 
: Figura(unArea) {
  this->l = l;
  l->agregarObservador( this );
}

ObjetoGui* FiguraLinea::getObjetoGui() {
  return this->l;
}

bool FiguraLinea::pertenece( int x, int y ) const {  
  float xi = l->getX();
  float yi = l->getY();
  float xf = l->getXFinal();
  float yf = l->getYFinal(); 
  
  float a = ( (yf-yi) / (xf-xi) );
  float b = yi - a*xi;

  float distancia = a*x - y + b;
  if ( distancia < 0 )
    distancia = distancia*-1;
  
  distancia = distancia / sqrt( pow(a,2) + 1 );
 
  int borde;
  l->getAttr( "borde", borde );

  return ( distancia < borde + MIN_SEL_LINEA );
}

Comportamiento* FiguraLinea::getComportamiento() {
  Comportamiento* c = new ComportamientoLinea( *l );
  return c;
}

Comportamiento* FiguraLinea::getComportamientoSeleccion() {
  return NULL;
}


void FiguraLinea::draw() {
  MyArea* area = getArea();
  Glib::RefPtr<Gdk::Window> window = area->get_window();
  Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

  int borde;
  ((ObjetoGui*)l)->getAttr( "borde", borde );
  cr->set_line_width(borde);

  Color c;
  std::string s("color");
  ((ObjetoGui*)l)->getAttr( s, c );
  double r,g,b;
  c.getCairoFormat( r,g,b );
  cr->set_source_rgb( r,g,b );

  cr->move_to( l->getX(), l->getY() );
  cr->line_to(l->getXFinal(), l->getYFinal() );

  cr->stroke();
}


Gtk::Window* FiguraLinea::getWindowParaConfigurar( int x , int y  ) {
  return NULL;
}
