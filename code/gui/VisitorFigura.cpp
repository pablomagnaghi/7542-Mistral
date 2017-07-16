#include "VisitorFigura.h"

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

#include "./../Visitor.h"
#include "./../Hoja.h"
#include "./../Linea.h"
#include "./../TextoFijo.h"
#include "./../TextoVariable.h"
#include "./../Calculo.h"
#include "./../ObjetoLista.h"

#include <iostream>

VisitorFigura::VisitorFigura( MyArea* a ) 
: area(a) {
  figuraCreada = NULL;
  l = NULL;
}

void VisitorFigura::visit( Hoja&  h ) {
}

void VisitorFigura::visit( Linea& lineaModelo ) {
}

void VisitorFigura::visit( TextoFijo& textoModelo ) {
  l = new TextoFijoGui( textoModelo );
  figuraCreada = new FiguraTextoFijo( (TextoFijoGui*)l, this->area );
}

void VisitorFigura::visit( TextoVariable& textoModelo ) {
  l = new TextoVariableGui( textoModelo );
  figuraCreada  = new FiguraTextoVariable( (TextoVariableGui*)l, this->area );
}

void VisitorFigura::visit( Calculo& calculoModelo ) {
  l = new CalculoGui( calculoModelo );
  figuraCreada = new FiguraCalculo( (CalculoGui*)l, this->area );
}

void VisitorFigura::visit( ObjetoLista& ) {
}

Figura* VisitorFigura::getFiguraCreada() {
  return figuraCreada;
}
  
VisitorFigura::~VisitorFigura() {
}
