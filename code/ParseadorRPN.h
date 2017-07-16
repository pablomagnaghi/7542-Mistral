#ifndef PARSEADORRPN_H_
#define PARSEADORRPN_H_

#include <iostream>
#include <string>

#define PRIORIDAD_UNO 1
#define PRIORIDAD_DOS 2

// Parseador para realizar el calculo en notacion polaca inversa
// recibe el calculo en cualquier notacion y transforma en
// notacion polaca inversa RPN

class ParseadorRPN {
private:
  std::string calculo;

  // calculo ya parseado para notacion polaca inversa (RPN)
  std::string calculoRPN;

  bool error;

  int prioridad( const char& );

  void obtenerRutaXpath( unsigned int& );
  void agregarElemento( const char& );
  void ordenarOperadoresPorPrioridad( std::string&, unsigned int&, unsigned int& pos );
  void cerrarParentesis( std::string&, unsigned int& );
  void obtenerOperador( std::string&, unsigned int& );
  void obtenerElementosCalculo( std::string&, unsigned int&, unsigned int& );

public:
  ParseadorRPN();

  bool esOperador( const char& );
  bool esOperando( const char& );

  void shuntingYard( const std::string& );

  std::string getCalculoRPN();

  bool getError();

  void reiniciar();

  virtual ~ParseadorRPN();
};

#endif /* PARSEADORRPN_H_ */
