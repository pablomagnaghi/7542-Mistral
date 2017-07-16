#ifndef _OBSERVADOR_H_INCLUDED_
#define _OBSERVADOR_H_INCLUDED_

#include <string>

class Observador {
public:
  virtual void notify() = 0;
};

#endif