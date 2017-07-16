#ifndef TEXTOVARIABLE_H_
#define TEXTOVARIABLE_H_
#include <iostream>
#include "Texto.h"

#define COD_UNO 1

class Visitor;

class TextoVariable : public Texto{
private:
  std::string textoXpath;

protected:
  // se redefinen para agregar textoXpath
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  TextoVariable( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto,
		  int size, const std::string& tipoFuente, const std::string& textoXpath);
  TextoVariable( std::string textoXpath );
  TextoVariable(XmlNodo* nodo);

  ObjetoGraficoRectangular* clone();

  virtual ~TextoVariable();

  void accept( Visitor* v );

  void setTextoXpath(const std::string& textoXpath);
  std::string getTextoXpath();

  XmlNodo toXml();

  // devuelve el xpath

  virtual std::string toString() const;

  virtual int getId() const;
};

#endif
