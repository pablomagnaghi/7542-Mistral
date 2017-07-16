#ifndef _DIALOG_NEW_DOC_TEMPLATE_
#define _DIALOG_NEW_DOC_TEMPLATE_

#include <gtkmm.h>

class DialogNewTemplate : public Gtk::Dialog {
  private:
    std::string nombre;
    std::string descripcion;

    Gtk::HBox boxNombre;
    Gtk::HBox boxDescripcion;

    Gtk::Entry	txtNombre;
    Gtk::Entry	txtDescripcion;

    Gtk::Label labelNombre;
    Gtk::Label labelDescripcion;

  public:
      DialogNewTemplate() {

	this->set_title( "Nuevo documento Template." );
	labelNombre.set_text("Nombre del documento:");
	labelDescripcion.set_text("Descripción:");

	boxNombre.pack_start( labelNombre );
	boxNombre.pack_start( txtNombre );

	boxDescripcion.pack_start( labelDescripcion );
	boxDescripcion.pack_start( txtDescripcion );

	this->get_vbox()->pack_start( boxNombre );
	this->get_vbox()->pack_start( boxDescripcion );

	this->add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	this->add_button( Gtk::Stock::OPEN, Gtk::RESPONSE_OK );

	labelNombre.show();
	labelDescripcion.show();
	txtDescripcion.show();
	txtNombre.show();
	boxNombre.show();
	boxDescripcion.show();
	this->show();
    }

    std::string getNombre() {
      return txtNombre.get_text();
    }

    std::string getDescripcion() {
      return txtDescripcion.get_text();
    }
};

#endif 

