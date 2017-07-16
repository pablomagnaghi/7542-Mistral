#ifndef _OBJETO_CON_ATRIBUTOS_H_INCLUDED_
#define _OBJETO_CON_ATRIBUTOS_H_INCLUDED_

#include <string>
#include <list>
#include "FormatoAtributo.h"
#include "Color.h"

class ObjetoConAtributos {
public:
  virtual void setAttr( const std::string& nombre, const std::string& valor ) = 0;
  virtual void setAttr( const std::string& nombre, bool valor ) = 0;
  virtual void setAttr( const std::string& nombre, int valor ) = 0;
  virtual void setAttr( const std::string& nombre, const Color& valor ) = 0;

  virtual void getAttr( const std::string& nombre, std::string& valor ) = 0;
  virtual void getAttr( const std::string& nombre, bool& valor ) = 0;
  virtual void getAttr( const std::string& nombre, int& valor ) = 0;
  virtual void getAttr( const std::string& nombre, Color& valor ) = 0;

  virtual void getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) = 0;
};

#endif