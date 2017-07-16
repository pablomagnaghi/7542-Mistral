#include "WindowNewVersion.h"

#include <gtkmm.h>
#include "./../Template.h"

WindowNewVersion::WindowNewVersion( const Template& t )
: labelDescripcion("Descripcion de la version:"),
  labelFechaDesde("Valido desde:"),
  checkFechaHasta("Con fecha final") {
  inicializarControles();

  this->entryDescripcion.set_text( t.getDescripcion() );

  Fecha fDesde;
  Fecha fHasta;

  fDesde = t.getValidoDesde();
  calendarFechaDesde.select_month( fDesde.getMes()-1, fDesde.getAnnio() );
  calendarFechaDesde.select_day( fDesde.getDia() );


  fHasta = t.getValidoHasta();
  if ( fHasta.getDia() == MAX_FECHA ) {
    checkFechaHasta.set_active( false );
    calendarFechaHasta.set_sensitive( false );
  }
  else {
    calendarFechaHasta.select_month( fHasta.getMes()-1, fHasta.getAnnio() );
    calendarFechaHasta.select_day( fHasta.getDia() );
    checkFechaHasta.set_active();
  }

}
WindowNewVersion::WindowNewVersion() 
: labelDescripcion("Descripcion de la version:"),
  labelFechaDesde("Valido desde:"),
  checkFechaHasta("con fecha final")  {
  inicializarControles();

  this->entryDescripcion.set_text( DEFAULT_DESCRIPCION_VERSION );
  checkFechaHasta.set_active();
}

void WindowNewVersion::inicializarControles() {
  boxDescripcion.add( labelDescripcion );
  boxDescripcion.add( entryDescripcion );
  this->get_vbox()->add( boxDescripcion );

  this->get_vbox()->add( labelFechaDesde );
  this->get_vbox()->add( calendarFechaDesde );

  this->get_vbox()->add( checkFechaHasta );
  this->get_vbox()->add( calendarFechaHasta );

  checkFechaHasta.signal_toggled().connect( mem_fun( *this, &WindowNewVersion::toogled ) );

  labelDescripcion.show();
  labelFechaDesde.show();

  entryDescripcion.show();
  calendarFechaDesde.show();
  calendarFechaHasta.show();

  boxDescripcion.show();
  checkFechaHasta.show();

  this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  this->set_title("Nueva version");
}

WindowNewVersion::~WindowNewVersion() {
}


std::string WindowNewVersion::getDescripcion() const {
  return this->entryDescripcion.get_text();
}

Fecha WindowNewVersion::getFechaDesde() const {
  guint dia, mes, annio;
  calendarFechaDesde.get_date( annio, mes, dia );
  Fecha f1( dia, mes+1, annio );
  return f1;
}

Fecha WindowNewVersion::getFechaHasta() const {
  if ( checkFechaHasta.get_active() ) {
    guint dia, mes, annio;
    calendarFechaHasta.get_date( annio, mes, dia );
    Fecha f1( dia, mes+1, annio );
    return f1;
  }
  else {
    Fecha f2;
    return f2;
  }
}
 