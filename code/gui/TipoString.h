#ifndef _TIPO_STRING_H_INCLUDED_
#define _TIPO_STRING_H_INCLUDED_

#include "TipoAtributo.h"

#include "ObjetoConAtributos.h"
#include <string>

#include <gtkmm.h>


class TipoString : public TipoAtributo {
private:
  Gtk::Label label;
  Gtk::Entry txt;
  Gtk::HBox hbox;

  void on_change ( Gtk::Entry* entry ) {
    this->getObjeto()->setAttr( this->getNombre(), entry->get_text() );
  }

public:
  TipoString( const std::string& nombre, ObjetoConAtributos* obj )
  : TipoAtributo( nombre,obj ), label(nombre) {

    std::string valor;
    this->getObjeto()->getAttr( getNombre(), valor );
    txt.set_text( valor );
    txt.signal_changed().connect( sigc::bind<Gtk::Entry*>(                           sigc::mem_fun( *this, &TipoString::on_change ), &txt ) );
    txt.show();
    label.show();
    hbox.pack_start( label );
    hbox.pack_start( txt );  
    hbox.show();

  }

  std::string toString() {
    std::string str;
    this->getObjeto()->getAttr( this->getNombre(), str );
    return str;
  }

  Gtk::Widget* widgetToSetValor() {
    return &hbox;
  }
    
};

#endif