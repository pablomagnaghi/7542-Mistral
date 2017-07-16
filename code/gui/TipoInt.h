#ifndef _TIPO_INT_H_INCLUDED_
#define _TIPO_INT_H_INCLUDED_

#include "TipoAtributo.h"

#include "ObjetoConAtributos.h"
#include <string>
#include <sstream>

#include <gtkmm.h>


class TipoInt : public TipoAtributo {
private:
  Gtk::Label label;
  Gtk::SpinButton spin;
  Gtk::HBox hbox;

  void on_change ( Gtk::SpinButton* entry ) {
    this->getObjeto()->setAttr( this->getNombre(), entry->get_value_as_int() );
  }

public:
  TipoInt( const std::string& nombre, ObjetoConAtributos* obj )
  : TipoAtributo( nombre,obj ), label(nombre), spin(1) {

    int valor;

    spin.signal_changed().connect( sigc::bind<Gtk::SpinButton*>(                           sigc::mem_fun( *this, &TipoInt::on_change ), &spin ) );
    spin.show();
    label.show();
    spin.set_wrap();
    spin.get_adjustment()->set_lower( 0 );
    spin.get_adjustment()->set_upper( 1000 );
    spin.get_adjustment()->set_step_increment( 1 );

    this->getObjeto()->getAttr( getNombre(), valor );
    spin.set_value( valor );

    hbox.pack_start( label );
    hbox.pack_start( spin );  
    hbox.show();
  }

  std::string toString() {
    int valor;
    this->getObjeto()->getAttr( this->getNombre(), valor );
    std::stringstream str;
    str << valor;
    return str.str();
  }

  Gtk::Widget* widgetToSetValor() {
    return &hbox;
  }
    
};

#endif