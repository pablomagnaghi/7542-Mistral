#ifndef LINEA_H_
#define LINEA_H_
#include <iostream>
#include "ObjetoGrafico.h"
#include "XmlNodo.h"

class Visitor;

class Linea : public ObjetoGrafico {
private:
  int posXfinal;
  int posYfinal;

protected:
  // redefinidos para agregar longitud
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );
public:
  Linea( int posX, int posY, int cR, int cV, int cA, int borde, int posXfinal, int posYfinal );
  Linea( int posX, int posY );
  Linea( XmlNodo* );

  virtual ~Linea();

  void accept( Visitor* v );

  int getPosXfinal() const;
  void setPosXfinal(int posXfinal );

  int getPosYfinal() const;
  void setPosYfinal(int posYfinal );

  XmlNodo toXml();
};

#endif /* LINEA_H_ */
