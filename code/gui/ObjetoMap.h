#ifndef _OBJETO_MAP_H_INCLUDED_
#define _OBJETO_MAP_H_INCLUDED_

#include <string>
#include "ObjetoConAtributos.h"
#include "Color.h"

#include <map>
class ObjetoMap :public ObjetoConAtributos {
private:
  std::map<std::string,std::string> cadenas;
  std::map<std::string,int> enteros;
  std::map<std::string,bool> booleanos;
  std::map<std::string,Color> colores;

public:
  void setAttr( const std::string& nombre, const std::string& valor );
  void setAttr( const std::string& nombre, bool valor );
  void setAttr( const std::string& nombre, int valor );
  void setAttr( const std::string& nombre, const Color& valor );

  void getAttr( const std::string& nombre, std::string& valor );
  void getAttr( const std::string& nombre, bool& valor );
  void getAttr( const std::string& nombre, int& valor );
  void getAttr( const std::string& nombre, Color& valor );

  void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );

};

#endif