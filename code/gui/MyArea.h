#ifndef _MYAREA_H_INCLUDED_
#define _MYAREA_H_INCLUDED_

#include <glibmm/refptr.h>
#include <gtkmm.h>
#include <cairomm/context.h>
#include <gdk/gdk.h>
#include <list>
#include <iostream>

#include "Figura.h"
#include "ObjetoGui.h"
#include "./../Hoja.h"
#include "TablaDePropiedades.h"
#include "Observador.h"
#include "ContextoEditor.h"


#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <cairomm/surface.h>


class Comportamiento;
class ComportamientoSeleccion;

class MyArea : public Gtk::DrawingArea, public Observador {

private:

  Hoja* miHoja;
  std::list<Figura*> misFiguras;
  std::list<ObjetoGui*> misObjetos;
  Comportamiento* miComportamiento;
  ComportamientoSeleccion* cSeleccion;

  TablaDePropiedades* tabla;
  ContextoEditor& contexto;

  Figura* figuraActual;

    Cairo::RefPtr< Cairo::Context > image_context_ptr_;
    Cairo::RefPtr< Cairo::ImageSurface > image_surface_ptr_;
    Glib::RefPtr< Gdk::Pixbuf > image_ptr_;
    bool tieneImagen;
    std::string fileImagen;

  /*
   * Borra los elementos de las listas de ObjetosGUI y figuras.
   * Liberando la memoria de cada objeto.
   * Primero se hace el delete de las figuras, y
   * luego de los objetosGUI.
   **/
  void limpiarObjetosYFiguras();

public:
  MyArea( TablaDePropiedades* tabla, ContextoEditor&  );

  bool cargarImagen( const std::string& path );
  void sacarImagen();
  std::string getImagen();
  bool tieneImagenDeFondo();

  void notify();

  void setHoja( Hoja* );
  Hoja* getHoja();

  void setComportamiento( Comportamiento* );
  void setComportamientoSeleccion( bool clearSeleccion = false, Figura* f = NULL );

  void drawAll( GdkEventExpose *event = NULL );
  Figura* seleccionar ( int x, int y );

  void addFigura( Figura* );
  void addObjetoGui( ObjetoGui* );
  void removeFigura( Figura* );
  void removeObjetoGui( ObjetoGui* );

  void removeActual();
  bool on_button_press_event (GdkEventButton* event);
  bool on_button_release_event (GdkEventButton* event);
  bool on_motion_notify_event (GdkEventMotion* event);
  bool on_expose_event( GdkEventExpose *event );
  bool on_key_press_event (GdkEventKey* event);

  bool on_click( GdkEventButton* event );
  bool on_double_click( GdkEventButton* event );
  virtual ~MyArea();
};
#endif