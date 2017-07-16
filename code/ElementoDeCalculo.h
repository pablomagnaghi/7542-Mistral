#ifndef ELEMENTODECALCULO_H_
#define ELEMENTODECALCULO_H_

#include "XmlNodo.h"
#include "Constantes.h"

class ElementoDeCalculo {
public:
  virtual int getValor( XmlNodo* ) const = 0;
  virtual std::string getContenido() const = 0;
  virtual void setContenido( const std::string& ) = 0;
  virtual XmlNodo toXml() = 0;

  virtual ~ElementoDeCalculo();
};

#endif /* ELEMENTODECALCULO_H_ */
