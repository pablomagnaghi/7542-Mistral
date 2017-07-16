#include "ParseadorRPN.h"

ParseadorRPN::ParseadorRPN() {
  this->error = false;
}

ParseadorRPN::~ParseadorRPN() {

}

int ParseadorRPN::prioridad(const char& c) {
  switch(c) {
    case '*':  case '/':
      return PRIORIDAD_DOS;
    case '+': case '-':
      return PRIORIDAD_UNO;
    default: return 0;
  }
}

void ParseadorRPN::obtenerRutaXpath( unsigned int& pos ) {
  std::string rutaXpath;

  rutaXpath += calculo[pos];
  pos++;

  while ( ( calculo[pos] != '"' ) && ( !error ) ) {
	rutaXpath += calculo[pos];
	if ( pos == calculo.size() ) {
	  rutaXpath = "";
	  error = true;
	}
	pos++;
  }

  if ( !error ) {
    rutaXpath += calculo[pos];
    calculoRPN += rutaXpath;
    pos++;
  }

}

// para separar los operandos de los operadores con
// caracter de espacio
void ParseadorRPN::agregarElemento( const char& c ) {
  calculoRPN += " ";
  calculoRPN += c;
  calculoRPN += " ";
}

void ParseadorRPN::ordenarOperadoresPorPrioridad( std::string& pila, unsigned int& posPila,
		unsigned int& pos ) {
  bool seguir = true;
  char c;

  while( ( posPila > 0 ) && ( seguir) ) {
	c = pila[posPila - 1];
	// op1 su prioridad es menor o igual a la de op2,
    if( ( esOperador( c ) ) && ( ( prioridad( calculo[pos] ) <= prioridad( c ) ) ) ) {
    	// Pop o2 de la pila, en la cola de salida;
    	agregarElemento( c );
    	posPila--;
    }
    else seguir = false;
  }
  // push op1 en la pila.
  pila[posPila] = calculo[pos];
  posPila++;
}

void ParseadorRPN::cerrarParentesis( std::string& pila, unsigned int& posPila ) {
  bool hayParentesis = false;
  char c;
  // Hasta que el símbolo en la parte superior de la pila es un paréntesis izquierdo,
  // pop operadores de la pila en la cola de salida
  while( (posPila > 0) && !hayParentesis ) {
	c = pila[posPila - 1];
	if ( c == '(' )
	  hayParentesis = true;
	else {
	  agregarElemento( c );
	  posPila--;
	}
  }

  // Si la pila se agota sin encontrar un paréntesis izquierdo, entonces hay paréntesis no coincidentes.
  if(!hayParentesis) {
  	// "Error: no hay parentesis coincidentes\n";
  	error = true;
  }
  // Pop del paréntesis de la izquierda de la pila, pero no en la cola de salida.
  posPila--;
}

void ParseadorRPN::obtenerOperador( std::string& pila, unsigned int& posPila ) {
  char c;

  while(posPila > 0) {
    c = pila[posPila - 1];
    if( ( c == '(' ) || ( c == ')' ) ) {
      //"Error: no hay parentesis coincidentes\n";
      error = true;
    }
    agregarElemento( c );
    posPila--;
  }
}

void ParseadorRPN::obtenerElementosCalculo( std::string& pila, unsigned int& posPila,
		unsigned int& pos ) {
  // Si el token es un número (identificador) se agrega a la cola de salida.
  if(esOperando(calculo[pos])) {
	if (calculo[pos] == '"')
	  obtenerRutaXpath( pos );
	else calculoRPN += calculo[pos];
  }
  // Si el token es un operador, entonces:
  else if(esOperador(calculo[pos])) {
	ordenarOperadoresPorPrioridad( pila, posPila, pos );
  }

  // Si el símbolo es a la izquierda, entre paréntesis a continuación, pulse sobre él la pila. /
  else if(calculo[pos] == '(') {
    pila[posPila] = calculo[pos];
	posPila++;
  }

  // Si el token es un paréntesis:
  else if(calculo[pos] == ')')
	cerrarParentesis( pila, posPila);
  else {
	// Error: token desconocido
	error = true;
  }
}

bool ParseadorRPN::esOperador( const char& c ) {
  return ( c == '+' || c == '-' || c == '/' || c == '*'  );
}

bool ParseadorRPN::esOperando( const char& c ) {
  return ( ( ( c >= '0' ) && ( c <= '9' ) ) || ( c == '"' ) );
}

void ParseadorRPN::shuntingYard( const std::string& calculo ) {
  this->calculo = calculo;
  unsigned int pos = 0;
  unsigned int posFinal = calculo.size();

  std::string pila;

  unsigned int posPila = 0;

  while( pos < posFinal ) {
    if( calculo[pos] != ' ' )
      obtenerElementosCalculo( pila, posPila, pos );
    else calculoRPN += " ";
    pos++;
  }

  obtenerOperador( pila,posPila );
}

std::string ParseadorRPN::getCalculoRPN() {
  return this->calculoRPN;
}

bool ParseadorRPN::getError() {
  return this->error;
}

void ParseadorRPN::reiniciar() {
  this->calculo = "";
  this->calculoRPN = "";
}

