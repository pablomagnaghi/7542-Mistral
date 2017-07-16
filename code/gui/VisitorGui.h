#ifndef _VISITOR_GUI_H_INCLUDED_
#define _VISITOR_GUI_H_INCLUDED_

#include "./../Visitor.h"
#include "./../Hoja.h"
#include "./../Linea.h"
#include "./../TextoFijo.h"
#include "./../TextoVariable.h"
#include "./../Calculo.h"
#include "./../ObjetoLista.h"

#include "MyArea.h"

class VisitorGui : public Visitor {
private:
  MyArea* area;

public:
  VisitorGui( MyArea* );
  virtual void visit( Hoja& );
  virtual void visit( Linea& );
  virtual void visit( TextoFijo& );
  virtual void visit( TextoVariable& );
  virtual void visit( Calculo& );
  virtual void visit( ObjetoLista& );
};


#endif