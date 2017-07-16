#ifndef _TIPO_BOOL_H_INCLUDED_
#define _TIPO_BOOL_H_INCLUDED_

#include "TipoAtributo.h"


#include "ObjetoConAtributos.h"
#include <string>

#include <gtkmm.h>

#define STRING_TRUE "True"
#define STRING_FALSE "False"

class TipoBool : public TipoAtributo {
private:
  Gtk::CheckButton check;

  void toogled ( Gtk::CheckButton* check ) {
    this->getObjeto()->setAttr( this->getNombre(), check->get_active() );
  }

public:
  TipoBool( const std::string& nombre, ObjetoConAtributos* obj )
  : TipoAtributo( nombre,obj ), check(nombre) {
    bool valor;
    this->getObjeto()->getAttr( getNombre(), valor );
    check.set_active(valor);
    check.signal_toggled().connect( sigc::bind<Gtk::CheckButton*>(               sigc::mem_fun( *this, &TipoBool::toogled ), &check ) );
    check.show();
  }

  std::string toString() {
    std::string str( STRING_FALSE );

    bool valor;
    this->getObjeto()->getAttr( this->getNombre(), valor );
    if ( valor )
      str = STRING_TRUE;

    return str;
  }

  Gtk::Widget* widgetToSetValor() {
    return &check;
  }
    
};

#endif