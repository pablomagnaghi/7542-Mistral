#include "Calculo.h"
#include "Visitor.h"

#include <iostream>

Calculo::Calculo()
: Texto() {
  cantOperandos = 0;
  cantOperadores = 0;
}

Calculo::Calculo( int posX, int posY, int cR, int cV, int cA, int borde, int ancho,
		int alto, int size, const std::string& tipoFuente )
: Texto( posX, posY, cR, cV, cA, borde, ancho, alto, size, tipoFuente ) {
  cantOperandos = 0;
  cantOperadores = 0;
}

Calculo::Calculo( XmlNodo* nodo ) {
  cantOperandos = 0;
  cantOperadores = 0;

  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);

  this->obtenerElementos(&nodoAux);

}

Calculo::~Calculo() {
  borrarElementos();
}

void Calculo::borrarElementos() {
  std::list<ElementoDeCalculo*>::iterator it = misElementos.begin();

  while ( it != misElementos.end() ) {
    delete (*it);
    it++;
  }

  misElementos.clear();
}

int Calculo::getIntFromString(const std::string& cadena) {
  int pos;
  std::stringstream buffer(cadena);
  buffer >> pos;
  return pos;
}

void Calculo::obtenerOperandoConstante( unsigned int& pos ) {
  std::string numero;

  numero += calculoRPN[pos];
  pos++;

  while ( ( calculoRPN[pos] >= '0' ) && ( calculoRPN[pos] <= '9' )  ) {
	  numero += calculoRPN[pos];
	  pos++;
  }

  ElementoDeCalculo* elemento = new OperandoConstante ( getIntFromString( numero ) );

  this->agregarElemento( elemento );

  cantOperandos++;

}

void Calculo::obtenerOperandoVariable( unsigned int& pos ) {
  std::string rutaXpath;

  pos++;
  rutaXpath += calculoRPN[pos];
  pos++;

  while ( calculoRPN[pos] != '"' ) {
	  rutaXpath += calculoRPN[pos];
	  pos++;
  }

  ElementoDeCalculo* elemento = new OperandoVariable ( rutaXpath );

  this->agregarElemento( elemento );

  cantOperandos++;

}

void Calculo::obtenerOperador( unsigned int& pos ) {
  std::string operador;
  switch( calculoRPN[pos] ) {
    case '+': operador = CALCULO_SUMA;
              break;
    case '-': operador = CALCULO_RESTA;
              break;
    case '*': operador = CALCULO_MULTIPLICACION;
              break;
    default: operador = CALCULO_DIVISION;
  }

  ElementoDeCalculo* elemento = new Operador ( operador );

  this->agregarElemento( elemento );

  cantOperadores++;
}

void Calculo::obtenerElementoDeCalculo( unsigned int& pos ) {

  if( parseador.esOperando(calculoRPN[pos] )) {
	if (calculoRPN[pos] == '"')
	  obtenerOperandoVariable( pos );
	else obtenerOperandoConstante( pos );
  }
  // Si el token es un operador, entonces:
  else if( parseador.esOperador(calculoRPN[pos] ))
	obtenerOperador( pos );

}

void Calculo::cargarListaDeElementos() {
  unsigned int pos = 0;

  while( pos < calculoRPN.size() ) {
	if( calculoRPN[pos] != ' ' )
	  obtenerElementoDeCalculo( pos );
	pos++;
  }
}


ObjetoGraficoRectangular* Calculo::clone() {
  return new Calculo( *this );
}

void Calculo::obtenerElementos ( XmlNodo* nodo) {
  while ( (nodo->esValido())  )
  {
	if ( nodo->getNombre() == "operandoConstante" ) {
	  ElementoDeCalculo* elemento = new OperandoConstante (nodo);
	  this->agregarElemento( elemento );
	  cantOperandos++;
	}

	if ( nodo->getNombre() == "operandoVariable" ) {
	  ElementoDeCalculo* elemento = new OperandoVariable (nodo);
	  this->agregarElemento( elemento );
	  cantOperandos++;
	}

	if ( nodo->getNombre() == "operador" ) {
	  ElementoDeCalculo* elemento = new Operador (nodo);
	  this->agregarElemento( elemento );
	  cantOperadores++;
	}
	*nodo = nodo->getHermano();
  }
}

void Calculo::agregarAtributos ( XmlNodo* nodo ) {
  Texto::agregarAtributos(nodo);

  XmlNodo nodoCalculo("calculo");
  nodoCalculo.setContenido( this->calculo );
  nodo->agregarHijo(nodoCalculo);
}

void Calculo::obtenerAtributos ( XmlNodo* nodo ) {
  Texto::obtenerAtributos(nodo);

  this->calculo = nodo->getContenido();
  *nodo = nodo->getHermano();
}

void Calculo::accept( Visitor* v ) {
  v->visit( *this );
}

void Calculo::agregarElemento( ElementoDeCalculo* elemento ) {
  this->misElementos.push_back( elemento );
}

std::list<ElementoDeCalculo*>::iterator Calculo::listaBegin() {
  return misElementos.begin();
}

std::list<ElementoDeCalculo*>::iterator Calculo::listaEnd() {
  return misElementos.end();
}

XmlNodo Calculo::toXml() {
  XmlNodo nodo("calculo");

  this->agregarPropiedades(&nodo);

  this->agregarAtributos(&nodo);

  std::list<ElementoDeCalculo*>::iterator i;

  for(i = this->listaBegin(); i != this->listaEnd(); ++i)
	nodo.agregarHijo((*i)->toXml());

  return nodo;
}

std::string Calculo::toString() const {
  std::string operacion("Operacion: ");
  operacion += calculo;
  return operacion;
}

bool Calculo::obtenerElementos( const std::string& calculo ) {
  this->calculo = calculo;
  calculoRPN = calculo;

  parseador.shuntingYard( calculoRPN );
  if ( parseador.getError() )
	return false;

  calculoRPN = parseador.getCalculoRPN();

  cargarListaDeElementos();

  return cantidadCorrecta();
}

bool Calculo::cantidadCorrecta() {
  return ( cantOperandos == cantOperadores + 1 );
}

void Calculo::reiniciarConteo() {
  cantOperandos = 0;
  cantOperadores = 0;
  parseador.reiniciar();
  borrarElementos();
}


std::string Calculo::getCalculo() {
  return this->calculo;
}

void Calculo::mostrar() {
  std::list<ElementoDeCalculo*>::iterator it = misElementos.begin();

  while ( it != misElementos.end() ) {
    std::cout << (*it)->getContenido() << std::endl;
    it++;
  }
}

int Calculo::getId() const {
  return COD_DOS;
}
