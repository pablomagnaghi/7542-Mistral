#ifndef OBJETOLISTA_H_
#define OBJETOLISTA_H_

#include "ObjetoGraficoRectangular.h"
#include "Texto.h"
#include "XmlNodo.h"
#include "Columna.h"

#include "Constantes.h"

#include <list>

class Visitor;

class ObjetoLista : public Texto {
private:
  std::string xpath;
  std::list<Columna*> misColumnas;

  void inicializarAltos();

  void obtenerObjetosLista( XmlNodo* );

protected:
  // redefinidos para agregar xpath
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  ObjetoLista( int posX, int posY, int cR, int cV, int cA, int borde, int ancho,
		  int alto, int size, const std::string& tipoFuente, const std::string& xpath );

  ObjetoLista( int ancho, int alto, const std::string& xpath );
  ObjetoLista( const std::string& xpath );
  ObjetoLista ( XmlNodo* );

  ObjetoGraficoRectangular* clone();

  void accept( Visitor* v );

  void setXpath(const std::string& );
  std::string getXpath();

  void agregarColumna( Columna* );
  void agregarColumna( std::string nombre, Texto* textoCuerpo, int ancho );

  bool agregarAdicional( int numColumna, Texto* );
  int getPosColumna( int numColumna );
  int getAltoCelda();

  Columna* getColumna( unsigned int pos );
  virtual void setAncho( int ancho );
  virtual void setSize( int size );

  void eliminarColumna( Columna* );
  void resizeColumna( Columna* col, int deltaX, bool ladoIzquierdo );
  int getCantidadDeColumnas() const;

  std::list<Columna*>::iterator columnasBegin();
  std::list<Columna*>::iterator columnasEnd();

  XmlNodo toXml();
  virtual ~ObjetoLista();

};

#endif /* OBJETOLISTA_H_ */
