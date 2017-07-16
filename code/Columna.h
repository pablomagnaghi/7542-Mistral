#ifndef _COLUMNA_H_INCLUDED_
#define _COLUMNA_H_INCLUDED_

#include "XmlNodo.h"
#include "Texto.h"
#include "TextoFijo.h"
#include "TextoVariable.h"
#include "Calculo.h"

#include <list>
#include <string>

class ObjetoLista;

enum t_celda {
		ENCABEZADO,
		CUERPO,
		ADICIONAL
	      };
typedef enum t_celda tipoCelda;

// La columna representa una celda de encabezado y una celda cuerpo de la lista.
// Cada Columna pertenece a una lista y tiene una pocisión dentro de ella.

class Columna {
private:
  int ancho;
  int porcentajeAnchoLista;

  int numColumna;

  TextoFijo* encabezado;
  Texto* cuerpo;
  std::list<Texto*> textosAdicionales;

  ObjetoLista& miLista;

  void agregarAtributos( XmlNodo* );
  void obtenerAtributos( XmlNodo* );
  void obtenerObjetosColumna( XmlNodo* );
  void obtenerTextoEncabezado( XmlNodo* );
  void obtenerTextoCuerpo( XmlNodo* );
  void obtenerTextoAdicional( XmlNodo* );

public:
  Columna( const std::string& nombreColumna, Texto* cuerpo, int ancho, ObjetoLista&  );

  // Metodos para cambiar los textos del cuerpo y el encabezado.

  TextoFijo* getEncabezado();

  Texto* getCuerpo( int numItem );
  void setCuerpo( Texto* );

  int getAncho();
  void setAncho( int ancho );

  void setAltoCelda( int alto );

  int getporcentajeAnchoLista();
  void setporcentajeAnchoLista( int porcentajeAnchoLista );

  int getNumColumna();
  void setNumColumna( int num );

  void agregarTextosAdicionales( Texto* );

  std::list<Texto*>::iterator listaBegin( int itemsEnLista );
  std::list<Texto*>::iterator listaEnd();

  Texto* getAdicional( int numAdicional );
  int getCantidadAdicionales() const;
  void eliminarAdicional( Texto* adicional );
  Columna( XmlNodo* nodo, ObjetoLista& );
  XmlNodo toXml() ;
  virtual ~Columna();

};

#endif
