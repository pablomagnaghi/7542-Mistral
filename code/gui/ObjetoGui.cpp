#include "ObjetoGui.h"

#include <gtkmm.h>
#include "./../Exceptions.h"
#include "./../Constantes.h"

  ObjetoGui::ObjetoGui( ObjetoGrafico* obj )
  :obj(obj) {
  }

  int ObjetoGui::getX() const {
    return obj->getPosX();
  }

  int ObjetoGui::getY() const {
    return MAXALTO - obj->getPosY();
  }

  void ObjetoGui::setX( int x ) {
    obj->setPosX(  x );
    this->notifyObservadores();
  }

  void ObjetoGui::setY( int y ) {
    obj->setPosY(  MAXALTO - y );
    this->notifyObservadores();
  }

  void ObjetoGui::setAttr( const std::string& nombre, const std::string& valor ) {
    throw new AtributoInvalidoExc( nombre );
  }

  void ObjetoGui::setAttr( const std::string& nombre, bool valor ) {
    throw new AtributoInvalidoExc( nombre );
  }

  void ObjetoGui::setAttr( const std::string& nombre, int valor ) {
    if ( nombre == "posX" )
      this->setX( valor );
    else if ( nombre == "posY" )
      this->setY( valor );
    else if ( nombre == "borde" )
      this->obj->setBorde( valor );
    else
      throw new AtributoInvalidoExc( nombre );
    this->notifyObservadores();
  }

  void ObjetoGui::setAttr( const std::string& nombre, const Color& valor ) {
    if ( nombre == "color" ) {
      this->obj->setColorRojo( valor.getRojo() );
      this->obj->setColorVerde( valor.getVerde() );
      this->obj->setColorAzul( valor.getAzul() );
    }
    else
      throw new AtributoInvalidoExc( nombre );
    this->notifyObservadores();
  }


  void ObjetoGui::getAttr( const std::string& nombre, std::string& valor ) {
    throw new AtributoInvalidoExc( nombre );
  }

  void ObjetoGui::getAttr( const std::string& nombre, bool& valor ) {
    throw new AtributoInvalidoExc( nombre );
  }

  void ObjetoGui::getAttr( const std::string& nombre, int& valor ) {
    if ( nombre == "posX" )
      valor = this->getX( );
    else if ( nombre == "posY" )
      valor = this->getY( );
    else if ( nombre == "borde" )
      valor = this->obj->getBorde( );
    else
      throw new AtributoInvalidoExc( nombre );  
  }

  void ObjetoGui::getAttr( const std::string& nombre, Color& valor ) {
    if ( nombre == "color" ) {
      valor.setRojo( this->obj->getColorRojo() );
      valor.setVerde( this->obj->getColorVerde() );
      valor.setAzul( this->obj->getColorAzul() );
    }
    else
      throw new AtributoInvalidoExc( nombre );
  }


  void ObjetoGui::getAtributos( std::list<FormatoAtributo>& listaDeAtributos ) {
    FormatoAtributo f1( "posX", ATTR_INT );
    FormatoAtributo f2( "posY", ATTR_INT );
    FormatoAtributo f3( "borde", ATTR_INT );
    FormatoAtributo f4( "color", ATTR_COLOR );

    listaDeAtributos.push_back( f1 );
    listaDeAtributos.push_back( f2 );
    listaDeAtributos.push_back( f3 );
    listaDeAtributos.push_back( f4 );
  }



