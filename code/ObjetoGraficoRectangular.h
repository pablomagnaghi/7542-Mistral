#ifndef OBJETOGRAFICORECTANGULAR_H_
#define OBJETOGRAFICORECTANGULAR_H_

#include "ObjetoGrafico.h"

class ObjetoGraficoRectangular : public ObjetoGrafico {
private:
  int ancho;
  int alto;
protected:
  // redefinidos para agregar size  y tipoFuente
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );
public:
  ObjetoGraficoRectangular ( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto );

  virtual ObjetoGraficoRectangular* clone() = 0;
  virtual void accept( Visitor* v ) = 0;

  ObjetoGraficoRectangular();

  virtual ~ObjetoGraficoRectangular();

  int getAncho() const;

  virtual void setAncho( int ancho );

  int getAlto() const;

  void setAlto( int alto );
};

#endif /* OBJETOGRAFICORECTANGULAR_H_ */
