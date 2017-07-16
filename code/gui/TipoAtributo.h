#ifndef _TIPO_ATRIBUTO_H_INCLUDED_
#define _TIPO_ATRIBUTO_H_INCLUDED_

#include "ObjetoConAtributos.h"
#include <string>

#include <gtkmm.h>

class TipoAtributo {
private:
  std::string nombreAtributo;
  ObjetoConAtributos* objeto;
public:
  TipoAtributo( const std::string& nombre, ObjetoConAtributos* obj )
  : nombreAtributo(nombre), objeto(obj) {
  }
  std::string getNombre() const {
    return this->nombreAtributo;
  }
  ObjetoConAtributos* getObjeto() const {
    return this->objeto;
  }

  virtual std::string toString() = 0;
  virtual Gtk::Widget* widgetToSetValor() = 0;  
};

#endif