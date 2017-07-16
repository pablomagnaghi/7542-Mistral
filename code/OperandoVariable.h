#ifndef OPERANDOVARIABLE_H_
#define OPERANDOVARIABLE_H_

#include "ElementoDeCalculo.h"

class OperandoVariable : public ElementoDeCalculo {
private:
  std::string xpath;
public:
  OperandoVariable( const std::string& xpath );
  OperandoVariable( XmlNodo* );
  virtual ~OperandoVariable();

  int getValor( XmlNodo* ) const;

  std::string getContenido() const;
  void setContenido( const std::string& );

  XmlNodo toXml();
};

#endif /* OPERANDOVARIABLE_H_ */
