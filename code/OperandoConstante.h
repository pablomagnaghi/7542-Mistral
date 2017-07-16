#ifndef OPERANDOCONSTANTE_H_
#define OPERANDOCONSTANTE_H_

#include "ElementoDeCalculo.h"

class OperandoConstante : public ElementoDeCalculo {
private:
  int valor;
public:
  OperandoConstante( const int& valor );
  OperandoConstante( XmlNodo* );

  virtual ~OperandoConstante();

  int getValor( XmlNodo* ) const;
  void setValor( const int& valor );

  std::string getContenido() const;
  void setContenido( const std::string& );

  XmlNodo toXml();
};

#endif /* OPERANDOCONSTANTE_H_ */
