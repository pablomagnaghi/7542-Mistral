#include "DialogoTestPostScript.h"
 
#include <gtkmm.h>


DialogoTestPostScript::DialogoTestPostScript( const std::string& tag,
					      const std::string& archivoDatosDef )
: labelDocDeDatos( "Documento de datos:" ), 
  labelArchivoDeSalida("Archivo postscript generado:") {

  this->set_title( "Test PostScript sobre versión de trabajo." );
  boxDocDeDatos.pack_start( labelDocDeDatos );
  boxDocDeDatos.pack_start( entryDocDeDatos );

  boxArchivoDeSalida.pack_start( labelArchivoDeSalida );
  boxArchivoDeSalida.pack_start( entryArchivoDeSalida );

  labelDocDeDatos.show();
  entryDocDeDatos.show();
  boxDocDeDatos.show();

  entryArchivoDeSalida.show();
  labelArchivoDeSalida.show();
  boxArchivoDeSalida.show();
  

  this->get_vbox()->add( boxDocDeDatos );
  this->get_vbox()->add( boxArchivoDeSalida );

  this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  this->entryDocDeDatos.set_text( archivoDatosDef );

  std::string archivoDeSalida = tag + ".ps";
  this->entryArchivoDeSalida.set_text( archivoDeSalida );
  
 
}
    

std::string DialogoTestPostScript::getArchivoDeDatos() {
  return this->entryDocDeDatos.get_text();
}

std::string DialogoTestPostScript::getArchivoDeSalida() {
  return this->entryArchivoDeSalida.get_text();
}
