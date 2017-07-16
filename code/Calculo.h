#ifndef CALCULO_H_
#define CALCULO_H_

#include <iostream>
#include <string>
#include <list>

#include "Texto.h"
#include "ElementoDeCalculo.h"
#include "Operador.h"
#include "OperandoConstante.h"
#include "OperandoVariable.h"

#include "ParseadorRPN.h"

#define CALCULO_SUMA		"add"
#define CALCULO_RESTA		"sub"
#define CALCULO_MULTIPLICACION	"mul"
#define CALCULO_DIVISION	"div"
#define COD_DOS 2

class Visitor;

class Calculo : public Texto {
private:
  std::list<ElementoDeCalculo*> misElementos;
  ParseadorRPN parseador;
  std::string calculo;
  std::string calculoRPN;

  int cantOperadores;
  int cantOperandos;

  void borrarElementos();

  int getIntFromString(const std::string& );
  void obtenerOperandoConstante( unsigned int& );
  void obtenerOperandoVariable( unsigned int& );
  void obtenerOperador( unsigned int& );
  void obtenerElementoDeCalculo( unsigned int& );
  void cargarListaDeElementos();

  void obtenerElementos ( XmlNodo* );

protected:
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  Calculo();
  Calculo( int posX, int posY, int cR, int cV, int cA, int borde,
		  int ancho, int alto, int size, const std::string& tipoFuente );
  Calculo( XmlNodo* nodo);

  virtual ~Calculo();

  ObjetoGraficoRectangular* clone();

  void accept( Visitor* v );

  void agregarElemento( ElementoDeCalculo* );

  std::list<ElementoDeCalculo*>::iterator listaBegin();

  std::list<ElementoDeCalculo*>::iterator listaEnd();

  XmlNodo toXml();

  virtual std::string toString() const;

  bool obtenerElementos( const std::string& );

  // la cantidad correcta para las operaciones
  // binarias +, -, *, / debe ser:
  // cantidad de operandos = cantidad de operadores + 1
  bool cantidadCorrecta();

  void reiniciarConteo();

  std::string getCalculo();

  void mostrar();
  virtual int getId() const;
};

#endif /* CALCULO_H_ */
