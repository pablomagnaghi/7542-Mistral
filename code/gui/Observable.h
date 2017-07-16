#ifndef _OBSERVABLE_H_INCLUDED_
#define _OBSERVABLE_H_INCLUDED_

class Observador;

#include <list>

class Observable {
private:
  std::list<Observador*> misObservadores;
public:
  void agregarObservador( Observador* );
  bool sacarObservador( Observador* );
  void notifyObservadores();
};

#endif 