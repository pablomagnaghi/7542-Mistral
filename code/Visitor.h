#ifndef _VISITOR_H_INCLUDED_
#define _VISITOR_H_INCLUDED_

#include "Hoja.h"
#include "Linea.h"
#include "TextoFijo.h"
#include "TextoVariable.h"
#include "Calculo.h"
#include "ObjetoLista.h"


// Patron visitor para recorrer la jerarquía de Objetos graficos.

class Visitor {
public:
  virtual void visit( Hoja& ) = 0;
  virtual void visit( Linea& ) = 0;
  virtual void visit( TextoFijo& ) = 0;
  virtual void visit( TextoVariable& ) = 0;
  virtual void visit( Calculo& ) = 0;
  virtual void visit( ObjetoLista& ) = 0;
};

#endif
