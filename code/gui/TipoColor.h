#ifndef _TIPO_COLOR_H_INCLUDED_
#define _TIPO_COLOR_H_INCLUDED_

#include "TipoAtributo.h"

#include "ObjetoConAtributos.h"
#include <string>
#include <sstream>

#include <gtkmm.h>


class TipoColor : public TipoAtributo {
private:
  Gtk::Label label;
  Gtk::ColorButton colorButton;
  Gtk::HBox hbox;
  
  void color_set ( Gtk::ColorButton* colorButton ) {
    Color c( colorButton->get_color() );
    this->getObjeto()->setAttr( this->getNombre(), c );
  }

public:
  TipoColor( const std::string& nombre, ObjetoConAtributos* obj )
  : TipoAtributo( nombre,obj ), label(nombre) {
    
    Color valor;
    this->getObjeto()->getAttr( this->getNombre(), valor );
    colorButton.set_color( valor.toGdkColor() );
    colorButton.signal_color_set().connect( sigc::bind<Gtk::ColorButton*>                      (sigc::mem_fun( *this, &TipoColor::color_set ), &colorButton ) );
    colorButton.show();
    label.show();

    hbox.pack_start( label );
    hbox.pack_start( colorButton );  
    hbox.show();
  }

  std::string toString() {
    Color valor;
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