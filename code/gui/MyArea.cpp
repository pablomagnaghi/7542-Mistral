#include "MyArea.h"

#include <glibmm/refptr.h>
#include <gtkmm.h>
#include <cairomm/context.h>
#include <gdk/gdk.h>
#include <list>
#include <iostream>

#include "Comportamiento.h"
#include "ObjetoGui.h"

#include "ObjetoGuiRectangular.h"
#include "FiguraRectangular.h"
#include "TablaDePropiedades.h"
#include "ComportamientoSeleccion.h"

#include "VisitorGui.h"

#include "ContextoEditor.h"

MyArea::MyArea(  TablaDePropiedades* tabla, ContextoEditor& ctx  )
:tabla(tabla), contexto(ctx) {
  this->add_events( Gdk::POINTER_MOTION_MASK );
  this->add_events( Gdk::BUTTON_PRESS_MASK  );
  this->add_events( Gdk::BUTTON_RELEASE_MASK );
  this->add_events( Gdk::KEY_PRESS_MASK  );
  this->add_events( Gdk::KEY_RELEASE_MASK );
  this->grab_focus();
  //rectanguloSeleccionado = NULL;
  miComportamiento = NULL;
  cSeleccion = NULL;
  figuraActual = NULL;
  miHoja = NULL;
  set_sensitive ( false );
  tieneImagen = false;
}

void MyArea::notify() {
  Hoja* hojaActual = NULL;
  if ( contexto.tieneVersionDeTrabajo() ) {
    hojaActual = contexto.getVersionDeTrabajo()->getHoja();
  }
  this->setHoja( hojaActual );
}

Figura* MyArea::seleccionar ( int x, int y ) {
  Figura* r = NULL;
  std::list<Figura*>::iterator it = misFiguras.begin();
  while ( (!r) && (it != misFiguras.end()) ) {
    if ( (*it)->pertenece( x, y ) ) {
      r = (*it);
    }
    it++;
  }
  return r;
}
  
std::string MyArea::getImagen() {
  return this->fileImagen;
}

bool MyArea::tieneImagenDeFondo() {
  return this->tieneImagen;
}
   
void MyArea::sacarImagen() {
  this->tieneImagen = false;
  this->drawAll();
}

bool MyArea::cargarImagen( const std::string& path ) {
    fileImagen = path;
    // Load pixbuf
    image_ptr_ = Gdk::Pixbuf::create_from_file ( path );
    
    // Detect transparent colors for loaded image
    Cairo::Format format = Cairo::FORMAT_RGB24;
    if (image_ptr_->get_has_alpha())
    {
        format = Cairo::FORMAT_ARGB32;
    }
    image_ptr_->add_alpha( false, 0.0,0.0,0.0 );
    // Create a new ImageSurface
    image_surface_ptr_ = Cairo::ImageSurface::create  (format, MAXANCHO, MAXALTO);
    
    // Create the new Context for the ImageSurface
    image_context_ptr_ = Cairo::Context::create (image_surface_ptr_);
 

    float xbase=float( image_ptr_->get_width() );
    float ybase=float( image_ptr_->get_height() );
    image_context_ptr_->scale(float(MAXANCHO)/xbase,float(MAXALTO)/ybase);

    // Draw the image on the new Context
    Gdk::Cairo::set_source_pixbuf (image_context_ptr_, image_ptr_, 0.0, 0.0);
    image_context_ptr_->paint();
    
    tieneImagen = true;
    this->drawAll();
    return true;
}  
// void sacarImagen();

void MyArea::drawAll( GdkEventExpose *event  ) {
  // Create the context for the widget
  Cairo::RefPtr<Cairo::Context> context = get_window()->create_cairo_context();

  if ( tieneImagen ) {
    if ( event ) {
      // Select the clipping rectangle
      context->rectangle(	event->area.x, event->area.y,
				event->area.width, event->area.height);
    
      context->clip();
    }

    // Store context
    context->save();


    // Draw the source image on the widget context
    context->set_source (image_surface_ptr_, 0.0, 0.0);
    context->rectangle (0.0, 0.0, MAXANCHO, MAXALTO );

    context->clip();

    context->paint();
    
    // Restore context
    context->restore();
  }
  else {
    context->set_source_rgb(1.0, 1.0, 1.0);
   context->paint();
  }
  context->set_source_rgb( 0,0,0 );
  context->move_to( MAXANCHO, 0 );
  context->line_to(MAXANCHO, MAXALTO );
  context->stroke();

  std::list<Figura*>::iterator it = misFiguras.begin();
  while ( it != misFiguras.end() ) {
    (*it)->draw();
    it++;
  }
}


void MyArea::setHoja( Hoja* h ) {
  if ( h ) {
    this->show();
    set_sensitive ( true );
    limpiarObjetosYFiguras();
    setComportamientoSeleccion( true );
    figuraActual = NULL;
    miHoja = NULL;

    VisitorGui v( this );
    h->accept( &v );
    this->drawAll();
    this->set_size_request( h->getAncho(), h->getAlto() );
  }
  else {
    //this->show();
    limpiarObjetosYFiguras();
    set_sensitive ( false );
    setComportamientoSeleccion( true );
    figuraActual = NULL;
    miHoja = NULL;
  }

  this->miHoja = h;
}


void MyArea::setComportamientoSeleccion( bool clearSeleccion, Figura* f  ) {
  static ComportamientoSeleccion cSeleccion1( this, *tabla ); 
  this->setComportamiento( &cSeleccion1 );
  this->cSeleccion = &cSeleccion1;

  if ( clearSeleccion )
    cSeleccion1.clear();
  if ( f )
    cSeleccion1.seleccionar( f );
}

Hoja* MyArea::getHoja() {
  return this->miHoja;
}

void MyArea::setComportamiento( Comportamiento* c ) {
  this->cSeleccion = NULL;
  this->miComportamiento = c;
}

void MyArea::addFigura( Figura* f ) {
  this->misFiguras.push_back( f );
}

void MyArea::addObjetoGui( ObjetoGui* obj ){
  this->misObjetos.push_back( obj );
}

void MyArea::removeFigura( Figura* f ) {
  misFiguras.remove( f );
}

void MyArea::removeObjetoGui( ObjetoGui* f ) {
  misObjetos.remove( f );
}

void MyArea::removeActual() {
  if ( this->cSeleccion != NULL )
    cSeleccion->removeActual();
}

bool MyArea::on_button_press_event (GdkEventButton* event) {
  bool result = true;
  if ( miComportamiento )
    result = miComportamiento->on_button_press_event( event );
  return result;
}

bool MyArea::on_button_release_event (GdkEventButton* event) {
  bool result = true;
  if ( miComportamiento )
    result = miComportamiento->on_button_release_event( event );
  return result;
}

bool MyArea::on_motion_notify_event (GdkEventMotion* event)  {
  bool result = true;
  if ( miComportamiento )
    result = miComportamiento->on_motion_notify_event( event );
  return result;
}

bool MyArea::on_key_press_event ( GdkEventKey* event ) {
  bool result = true;
  if ( miComportamiento )
    result = miComportamiento->on_key_press_event( event );
  return result;
}

bool MyArea::on_expose_event( GdkEventExpose *event ) {
  this->drawAll(event);
  return true;
}
  
void MyArea::limpiarObjetosYFiguras() {
  std::list<Figura*>::iterator it = misFiguras.begin();
  while ( it != misFiguras.end() ) {
    delete (*it);
    it++;
  }

  misFiguras.clear();

  std::list<ObjetoGui*>::iterator it2 = misObjetos.begin();
  while ( it2 != misObjetos.end() ) {
    delete (*it2);
    it2++;
  }

  misObjetos.clear();
}
  


MyArea::~MyArea() {
  limpiarObjetosYFiguras();
}

