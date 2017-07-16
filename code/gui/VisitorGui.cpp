#include "VisitorGui.h"

#include "./../Visitor.h"
#include "./../Hoja.h"
#include "./../Linea.h"
#include "./../TextoFijo.h"
#include "./../TextoVariable.h"
#include "./../Calculo.h"
#include "./../ObjetoLista.h"

#include "MyArea.h"

#include <list>
#include "./../ObjetoGrafico.h"

#include "FiguraLinea.h"
#include "LineaGui.h"

#include "TextoFijoGui.h"
#include "FiguraTextoFijo.h"

#include "TextoVariableGui.h"
#include "FiguraTextoVariable.h"

#include "CalculoGui.h"
#include "FiguraCalculo.h"

#include "ListaGui.h"
#include "FiguraLista.h"

#include "./../Visitor.h"
#include "./../Hoja.h"
#include "./../Linea.h"
#include "./../TextoFijo.h"
#include "./../TextoVariable.h"
#include "./../Calculo.h"
#include "./../ObjetoLista.h"

VisitorGui::VisitorGui( MyArea*  a ) 
: area(a) {
}

void VisitorGui::visit( Hoja&  h ) {
  if ( this->area ) {
    std::list<ObjetoGrafico*>::iterator it = h.listaBegin();
    while ( it != h.listaEnd() ) {
      (*it)->accept( this );
      it++;
    }
  }
}

void VisitorGui::visit( Linea& lineaModelo ) {
  LineaGui* l = new LineaGui( lineaModelo );
  FiguraLinea* f = new FiguraLinea( l, this->area );
  this->area->addFigura( f );
  this->area->addObjetoGui( l );
}

void VisitorGui::visit( TextoFijo& textoModelo ) {
  TextoFijoGui* l = new TextoFijoGui( textoModelo );
  FiguraTextoFijo* f = new FiguraTextoFijo( l, this->area );
  this->area->addFigura( f );
  this->area->addObjetoGui( l );

  std::cout << std::endl << "Dibujando txt fijo" << textoModelo.toString() << " en pos" << 
  textoModelo.getPosY() << " de alto " << textoModelo.getAlto();
}

void VisitorGui::visit( TextoVariable& textoModelo ) {
  TextoVariableGui* l = new TextoVariableGui( textoModelo );
  FiguraTextoVariable* f = new FiguraTextoVariable( l, this->area );
  this->area->addFigura( f );
  this->area->addObjetoGui( l );
}

void VisitorGui::visit( Calculo& calculoModelo ) {
  CalculoGui* l = new CalculoGui( calculoModelo );
  FiguraCalculo* f = new FiguraCalculo( l, this->area );
  this->area->addFigura( f );
  this->area->addObjetoGui( l );
}

void VisitorGui::visit( ObjetoLista& lista ) {
  ListaGui* l = new ListaGui( lista );
  FiguraLista* f = new FiguraLista( l, this->area );
  this->area->addFigura( f );
  this->area->addObjetoGui( l );
}
