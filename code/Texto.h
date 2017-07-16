#ifndef TEXTO_H_
#define TEXTO_H_

#include "ObjetoGraficoRectangular.h"

#define COD_ERROR -1

class Texto : public ObjetoGraficoRectangular{
private:
  int size;
  std::string tipoFuente;

protected:
  // redefinidos para agregar size  y tipoFuente
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  Texto ( int posX, int posY, int cR, int cV, int cA, int borde,
		  int ancho, int alto, int size, const std::string& tipoFuente );
  Texto();
  virtual void accept( Visitor* v ) = 0;

  virtual ~Texto();

  int getSize() const;
  virtual void setSize( int size );

  std::string getTipoFuente() const;
  void setTipoFuente( const std::string& fuente );


  // Devuelve una representación en texto de su contenido.
  // El texto fijo devuelve su texto, el variable su Xpath y
  // cálculo alguna otra representación.

  virtual std::string toString() const;
  virtual int getId() const;

};

#endif /* TEXTO_H_ */
