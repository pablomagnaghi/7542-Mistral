#ifndef OPERADOR_H_
#define OPERADOR_H_

#include "ElementoDeCalculo.h"

class Operador : public ElementoDeCalculo {
private:
  std::string operador;
public:
  Operador( const std::string& );
  Operador( XmlNodo* );

  int getValor( XmlNodo* ) const;
  std::string getContenido() const;
  void setContenido( const std::string& );
  XmlNodo toXml();

  virtual ~Operador();
};

#endif /* OPERADOR_H_ */
