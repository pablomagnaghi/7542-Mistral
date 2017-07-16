#ifndef OBJETOGRAFICO_H_
#define OBJETOGRAFICO_H_
#include <iostream>
#include "XmlNodo.h"
#include "Constantes.h"
#include <sstream>

class Visitor;

class ObjetoGrafico {
private:
  int posX;
  int posY;
  int colorRojo;
  int colorVerde;
  int colorAzul;
  int borde;

protected:
  // si hay que agregar más propiedades, se redefinen
  virtual void agregarPropiedades (XmlNodo* nodo);
  virtual void obtenerPropiedades (XmlNodo* nodo);

  // si hay que agregar más atributos, se redefinen
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  ObjetoGrafico( int x, int y, int cR, int cV, int cA, int borde );
  ObjetoGrafico();

  virtual ~ObjetoGrafico();

  virtual void accept( Visitor* v ) = 0;

  int getPosX() const;
  int getPosY() const;

  void setPosX(int posX);
  void setPosY(int posY);

  int getColorRojo() const;
  void setColorRojo( int color );

  int getColorVerde() const;
  void setColorVerde( int color );

  int getColorAzul() const;
  void setColorAzul( int color );

  int getBorde() const;
  void setBorde( int borde );

  virtual XmlNodo toXml() = 0;
};

#endif
