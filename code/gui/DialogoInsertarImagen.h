#ifndef _DIALOGO_INSERTAR_IMAGEN_H_INCLUDED_
#define _DIALOGO_INSERTAR_IMAGEN_H_INCLUDED_

#include <gtkmm.h>
#include <string>
#include "./../Template.h"
#include "./../Fecha.h"


class DialogoInsertarImagen : public Gtk::Dialog {
private:

  Gtk::HBox boxDescripcion;
  Gtk::Label labelDescripcion;
  Gtk::Entry entryArchivo;
  Gtk::Button archivoButton;

  void on_button_clicked() {
     Gtk::FileChooserDialog dialog( "Seleccionar imágen...",
				    Gtk::FILE_CHOOSER_ACTION_OPEN );
 
     //Add response buttons the the dialog:
     dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
     dialog.add_button("Select", Gtk::RESPONSE_OK);
 
     int result = dialog.run();
 
     if ( result == Gtk::RESPONSE_OK ) {
       std::string fileName = dialog.get_filename();
       entryArchivo.set_text(fileName );
    }
  }

public:
  DialogoInsertarImagen( const std::string& archivoActual, bool tieneImagen ) {

    boxDescripcion.pack_start( labelDescripcion );
    boxDescripcion.pack_start( entryArchivo );
    boxDescripcion.pack_start( archivoButton  );

    if ( tieneImagen ) {
      this->add_button(Gtk::Stock::CLEAR, 7);
      entryArchivo.set_text( archivoActual );
    }
    this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

    archivoButton.set_label("...");
    archivoButton.signal_clicked().connect(sigc::mem_fun(*this,&DialogoInsertarImagen:: on_button_clicked));

    this->get_vbox()->add( boxDescripcion );

    boxDescripcion.show();
    labelDescripcion.show();
    entryArchivo.show();
    archivoButton.show();

  }

  std::string getArchivoDeImagen() {
    return entryArchivo.get_text();
  }
};

#endif
