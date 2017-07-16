#ifndef _DIALOG_FORMAT_CELDA_H_INCLUDED
#define _DIALOG_FORMAT_CELDA_H_INCLUDED

#include <gtkmm.h>
#include "./../Texto.h"
#include "./../Columna.h"

#include <string>

enum t_texto {
		  TEXTO_FIJO = 0,
		  TEXTO_VARIABLE,
		  CALCULO 
		};

typedef enum t_texto tFormatoTexto;

class DialogFormatoCelda : public Gtk::Dialog {
  private:
    tipoCelda tipo;
    std::string texto;
    tFormatoTexto formato;

    Gtk::HBox boxTipo;
    Gtk::Label labelTipo;
    Gtk::ComboBoxText combo;

    Gtk::HBox boxEntry;
    Gtk::Label labelEntry;
    Gtk::Entry	txtTexto;

   void on_combo_changed() {
      Glib::ustring text = combo.get_active_text();
      if( !(text.empty()) ) {
	if ( text == "TEXTO FIJO" ) {
	  labelEntry.set_text("Texto:");
	    formato = TEXTO_FIJO;
	}
	if ( text == "TEXTO VARIABLE" ) {
	  labelEntry.set_text("Xpath:");
	    formato = TEXTO_VARIABLE;
	}
	if ( text == "CALCULO" ) {
	  labelEntry.set_text("Operación:");
	    formato = CALCULO;
	}
	txtTexto.set_text( texto );
      }
  }

  void on_change () {
    this->texto = txtTexto.get_text();
  }

  public:
    DialogFormatoCelda( std::string texto, tipoCelda tipo, int id =-1  )
    : tipo(tipo), texto(texto)  {

	this->set_title( "Formato de celda." );

	labelTipo.set_text("Tipo de celda:");
	combo.append_text("TEXTO FIJO");
	combo.append_text("TEXTO VARIABLE");
	combo.append_text("CALCULO");

	if ( tipo == ENCABEZADO ) {
	  combo.set_active_text("TEXTO FIJO");
	  combo.set_sensitive( false );
	}
	else {
	  if ( id == 0 )
	    combo.set_active_text("TEXTO FIJO");
	    formato = TEXTO_FIJO;
	  if ( id == 1 )
	    combo.set_active_text("TEXTO VARIABLE");
	    formato = TEXTO_VARIABLE;
	  if ( id == 2 )
	    combo.set_active_text("CALCULO");
	    formato = CALCULO;
	}

	combo.signal_changed().connect(sigc::mem_fun(*this,
              &DialogFormatoCelda::on_combo_changed) );
	  
	txtTexto.signal_changed().connect(sigc::mem_fun(*this,
              &DialogFormatoCelda::on_change) );

	boxTipo.pack_start( labelTipo );
	boxTipo.pack_start( combo );

	labelEntry.set_text("texto");
	txtTexto.set_text( texto );
	boxEntry.pack_start( labelEntry );
	boxEntry.pack_start( txtTexto );

	this->get_vbox()->pack_start( boxTipo );
	this->get_vbox()->pack_start( boxEntry );

	this->add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
	this->add_button( Gtk::Stock::OPEN, Gtk::RESPONSE_OK );

	labelTipo.show();
	labelEntry.show();
	combo.show();
	txtTexto.show();
	boxTipo.show();
	boxEntry.show();
	this->show();
    }

    const std::string& getTexto() const {
      return texto;
    }

    tFormatoTexto getTipoSeleccionado() const {
      return formato;
    }

};

#endif 

