#include "ObjetoMap.h"

#include <string>
#include "ObjetoConAtributos.h"
#include "FormatoAtributo.h"
#include <list>
#include "Color.h"

#include <map>
#include <iostream>

/*
  std::map<std::string,std::string> cadenas;
  std::map<std::string,int> enteros;
  std::map<std::string,bool> booleanos;
  std::map<std::string,t_color> colores;
*/

void ObjetoMap::setAttr( const std::string& nombre, const std::string& valor ) {
  this->cadenas[ nombre ] =valor;
  std::cout << std::endl << "Cambio valor de " << nombre << " = " << valor;
  std::cout.flush();
}

void ObjetoMap::setAttr( const std::string& nombre, bool valor ) {
  this->booleanos[ nombre ] =valor;
  std::cout << std::endl << "Cambio valor de " << nombre << " = " << valor;
  std::cout.flush();
}

void ObjetoMap::setAttr( const std::string& nombre, int valor ) {
  this->enteros[ nombre ] =valor;
  std::cout << std::endl << "Cambio valor de " << nombre << " = " << valor;
  std::cout.flush();
}

void ObjetoMap::setAttr( const std::string& nombre, const Color& valor ) {
  this->colores[ nombre ] =valor;
  std::cout << std::endl << "Cambio valor de " << nombre << " = " << valor;
  std::cout.flush();
}


void ObjetoMap::getAttr( const std::string& nombre, std::string& valor ) {
  std::map<std::string,std::string>::iterator it  = cadenas.find( nombre );
  if ( it != cadenas.end() ){
    valor = it->second;
  }
}

void ObjetoMap::getAttr( const std::string& nombre, bool& valor ) {
  std::map<std::string,bool>::iterator it  = booleanos.find( nombre );
  if ( it != booleanos.end() ){
    valor = it->second;
  }
}

void ObjetoMap::getAttr( const std::string& nombre, int& valor ) {
  std::map<std::string,int>::iterator it  = enteros.find( nombre );
  if ( it != enteros.end() ){
    valor = it->second;
  }
}

void ObjetoMap::getAttr( const std::string& nombre, Color& valor ) {
  std::map<std::string,Color>::iterator it  = colores.find( nombre );
  if ( it != colores.end() ){
    valor = it->second;
  }
}

void ObjetoMap::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {

  std::map<std::string,std::string>::iterator it1  = cadenas.begin();
  while ( it1 != cadenas.end() ) {
    FormatoAtributo attr( it1->first, ATTR_STRING );
    listaDeAtributos.push_back( attr );
    it1++;
  }

  std::map<std::string,bool>::iterator it2  = booleanos.begin();
  while ( it2 != booleanos.end() ) {
    FormatoAtributo attr( it2->first, ATTR_BOOL );
    listaDeAtributos.push_back( attr );
    it2++;
  }

  std::map<std::string,int>::iterator it3  = enteros.begin();
  while ( it3 != enteros.end() ) {
    FormatoAtributo attr( it3->first, ATTR_INT );
    listaDeAtributos.push_back( attr );
    it3++;
  }

  std::map<std::string,Color>::iterator it4  = colores.begin();
  while ( it4 != colores.end() ) {
    FormatoAtributo attr( it4->first, ATTR_COLOR );
    listaDeAtributos.push_back( attr );
    it4++;
  }
}

