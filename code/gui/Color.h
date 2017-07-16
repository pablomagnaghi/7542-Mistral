#ifndef _COLOR_H_INCLUDED_
#define _COLOR_H_INCLUDED_

#define MAX_INTENSIDAD	65536

#include <gtkmm.h>
#include <iostream>

class Color {
private:
  int rojo;
  int verde;
  int azul;

  int format( const int& intensidad ) const {
    if ( intensidad<0 )
      return 0;
    if ( intensidad>MAX_INTENSIDAD )
      return MAX_INTENSIDAD;
    return intensidad;
  }
public:
  Color( const Gdk::Color& c ) {
    setRojo( c.get_red() );
    setVerde( c.get_green() );
    setAzul( c.get_blue() );
  }

  Color() {
    setRojo( 0 );
    setVerde( 0 );
    setAzul( 0 );
  }
  Color( int intensidadRojo, int intensidadVerde, int intensidadAzul ) {
    setRojo( intensidadRojo );
    setVerde( intensidadVerde );
    setAzul( intensidadAzul );
  }
  int getRojo() const {
    return rojo;
  }
  int getVerde() const {
    return verde;
  }
  int getAzul() const {
    return azul;
  }
  void setRojo( const int& intensidad ) {
    rojo = format( intensidad );
  }
    
  void setVerde( const int& intensidad ) {
    verde = format( intensidad );
  }

  void setAzul( const int& intensidad ) {
    azul = format( intensidad );
  }

  void getCairoFormat( double& R, double& G, double& B ) {
    R = getRojo() / (double)MAX_INTENSIDAD;
    G = getVerde() / (double)MAX_INTENSIDAD;
    B = getAzul() / (double)MAX_INTENSIDAD;
  }

  Gdk::Color toGdkColor() const {
    Gdk::Color c;
    c.set_red( rojo );
    c.set_green( verde );
    c.set_blue( azul );
    return c;
  }

  friend std::ostream& operator<< ( std::ostream& str, const Color& c ) {
    str << "( R=" << c.rojo << " ; G=" << c.verde << " ; B=" << c.azul << " )";
    return str;
  }
};

#endif