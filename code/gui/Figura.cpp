#include "Figura.h"

#include <glibmm/refptr.h>
#include <cairomm/context.h>

#include "MyArea.h"

Figura::Figura(  MyArea* unArea )
: area(unArea) {
  this->setSeleccionada( false );
}

void Figura::notify() {
  this->getArea()->drawAll();
}

MyArea* Figura::getArea() {
  return this->area;
}

