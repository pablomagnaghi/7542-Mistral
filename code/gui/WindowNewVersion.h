#ifndef _WINDOW_NEW_VERSION_H_INCLUDED_
#define _WINDOW_NEW_VERSION_H_INCLUDED_

#include <gtkmm.h>
#include <string>
#include "./../Template.h"
#include "./../Fecha.h"

#define DEFAULT_DESCRIPCION_VERSION  "Descripcion de una version..."

class WindowNewVersion : public Gtk::Dialog {
private:

  Gtk::HBox boxDescripcion;
  Gtk::Label labelDescripcion;
  Gtk::Entry entryDescripcion;

  Gtk::HBox boxFechaDesde;
  Gtk::Label labelFechaDesde;
  Gtk::Calendar calendarFechaDesde;

  Gtk::HBox boxFechaHasta;
/*  Gtk::Label labelFechaHasta;*/
  Gtk::Calendar calendarFechaHasta;

  Gtk::CheckButton checkFechaHasta;
  void inicializarControles();

  void toogled ( ) {
      calendarFechaHasta.set_sensitive( checkFechaHasta.get_active() );
  }

public:
  WindowNewVersion( const Template& );
  WindowNewVersion();
  ~WindowNewVersion();

  std::string getDescripcion() const;
  Fecha getFechaDesde() const;
  Fecha getFechaHasta() const;

};

#endif
