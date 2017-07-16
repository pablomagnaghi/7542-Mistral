#ifndef _FORMATO_ATRIBUTO_H_INCLUDED_
#define _FORMATO_ATRIBUTO_H_INCLUDED_

#include <string>

enum tipoAtributo {
		    ATTR_STRING,
		    ATTR_BOOL,
		    ATTR_INT,
		    ATTR_COLOR
		    };

typedef enum tipoAtributo t_atributo;

class FormatoAtributo {
private:
  std::string nombre;
  t_atributo tipo;
public:
  FormatoAtributo( const std::string& nombre, t_atributo tipo )
  : nombre(nombre), tipo(tipo) {
  }
  const std::string& getNombre() const {
    return nombre;
  }
  t_atributo getTipo() const {
    return tipo;
  }
};


#endif