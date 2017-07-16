#ifndef _OBJETO_GUI_H_INCLUDED_
#define _OBJETO_GUI_H_INCLUDED_

#include "Observable.h"
#include "ObjetoConAtributos.h"
#include "./../ObjetoGrafico.h"


class ObjetoGui : public Observable, public ObjetoConAtributos {

private:
  ObjetoGrafico* obj;
public:

  ObjetoGui( ObjetoGrafico* obj );

  ObjetoGrafico* getObjetoGrafico() {
    return obj;
  }

  virtual int getX() const;
  virtual int getY() const;
  virtual void setX( int x );
  virtual void setY( int y );

  virtual void setAttr( const std::string& nombre, const std::string& valor );
  virtual void setAttr( const std::string& nombre, bool valor );
  virtual void setAttr( const std::string& nombre, int valor );
  virtual void setAttr( const std::string& nombre, const Color& valor );

  virtual void getAttr( const std::string& nombre, std::string& valor ) ;
  virtual void getAttr( const std::string& nombre, bool& valor );
  virtual void getAttr( const std::string& nombre, int& valor );
  virtual void getAttr( const std::string& nombre, Color& valor );

  virtual void getAtributos( std::list<FormatoAtributo>& listaDeAtributos );
};

#endif