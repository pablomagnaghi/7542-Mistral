#include "Observable.h"

#include "Observador.h"
#include <list>

void Observable::agregarObservador( Observador* o ) {
  bool result = false;
  std::list<Observador*>::iterator it = misObservadores.begin();

  while ( (it!=misObservadores.end()) && (!result) ) {
    result = ( (*it) == o );
    it++;
  }

  if ( !result ) {
    misObservadores.push_back( o );
  }
}

bool Observable::sacarObservador( Observador* o ) {
  bool result = false;
  std::list<Observador*>::iterator it = misObservadores.begin();

  while ( (it!=misObservadores.end()) && (!result) ) {
    result = ( (*it) == o );

    if ( result ) 
      misObservadores.erase( it );
    else
      it++;
  }
  return result;
}

void Observable::notifyObservadores() {
  std::list<Observador*>::iterator it = misObservadores.begin();
  for ( it = misObservadores.begin(); it != misObservadores.end(); it++ ) {
    (*it)->notify();
  }
}


