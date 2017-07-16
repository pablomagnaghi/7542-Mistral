#ifndef TEXTOFIJO_H_
#define TEXTOFIJO_H_
#include <iostream>
#include <string>

#include "Texto.h"

class Visitor;

class TextoFijo : public Texto {
private:
  std::string texto;
protected:
  // redefinidos para agregar texto
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  TextoFijo( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto,
		  int size, const std::string& tipoFuente, const std::string& texto);
  TextoFijo( const std::string& texto );
  TextoFijo( XmlNodo* );

  ObjetoGraficoRectangular* clone();

  virtual ~TextoFijo();

  void accept( Visitor* v );

  std::string getTexto() const;
  void setTexto(const std::string& texto);

  XmlNodo toXml();

  // devuelve el texto.

  virtual std::string toString() const;
  virtual int getId() const;

};

#endif /* TEXTOFIJO_H_ */
