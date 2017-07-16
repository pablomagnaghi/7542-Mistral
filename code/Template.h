#ifndef _TEMPLATE_H_INCLUDED_
#define _TEMPLATE_H_INCLUDED_

#include "Fecha.h"
#include "XmlNodo.h"
#include "Hoja.h"

#include <string>

// Clase que representa un único template.
// Posee una fecha de validez y un objetoGrafico que es la
// hoja principal.
// Para dibujar hacer Template->getHoja.visit( visitorPostScript )

class Template {
private:
  Fecha hasta;
  Fecha desde;
  std::string descripcion;
  Hoja* hoja;

public:
  // Crea un Template a partir de un nodo existente.
  Template( XmlNodo* );

  // Crea un template nuevo con un alto y ancho de hoja.
  Template( int ancho, int alto, const Fecha& desde, const Fecha& hasta, const std::string desc );
  Template( std::string tipoHoja, const Fecha& desde, const Fecha& hasta, const std::string desc  );

  // Retorna un objeto gráfico que representa a la hoja del template
  // y contine todos los objetos gráficos.

  Hoja* getHoja();

  const Fecha& getValidoDesde() const;
  void setValidoDesde( const Fecha& );

  const Fecha& getValidoHasta() const;
  void setValidoHasta( const Fecha& );

  void setDescripcion( const std::string& );
  const std::string& getDescripcion() const;
  XmlNodo toXml();

  std::string toString() const;
  virtual ~Template();
};

#endif
