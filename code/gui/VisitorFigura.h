#ifndef _VISITOR_FIGURA_H_INCLUDED_
#define _VISITOR_FIGURA_H_INCLUDED_

#include "./../Visitor.h"
#include "./../Hoja.h"
#include "./../Linea.h"
#include "./../TextoFijo.h"
#include "./../TextoVariable.h"
#include "./../Calculo.h"
#include "./../ObjetoLista.h"
#include "Figura.h"
#include "ObjetoGui.h"
#include "MyArea.h"

class VisitorFigura : public Visitor {
private:
  MyArea* area;
  Figura* figuraCreada;
  ObjetoGui* l;

public:
  VisitorFigura (MyArea*);
  virtual void visit( Hoja& );
  virtual void visit( Linea& );
  virtual void visit( TextoFijo& );
  virtual void visit( TextoVariable& );
  virtual void visit( Calculo& );
  virtual void visit( ObjetoLista& );

  Figura* getFiguraCreada();
  ~VisitorFigura();
};


#endif