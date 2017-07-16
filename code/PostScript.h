#ifndef POSTSCRIPT_H_
#define POSTSCRIPT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Constantes.h"

class PostScript {
private:
  std::ostream& archivo;

  std::string getColor( int );

public:
  PostScript( std::ostream& );

  virtual ~PostScript();

  void moveto( int, int );

  void setrgbcolor( int, int, int );

  void rlineto( int, int );

  void lineto( int, int );

  void setlinewidth( int );

  void fill();

  void bordear( int, int, int, int, int, int, int, int );

  void definirVariables( int, int, int, int, int, int );

  void truncarTexto( int, int, int, int );

  void newline();

  void prtstr();

  void escritura( const std::string& );

  void setfont( int, const std::string& );

  void main( int, int, int );

  void ptr();

  // posX, posY, cR, cV, cA, borde, ancho, alto, tipoHoja
  void crearRecuadro( int, int, int, int, int, int, int, int );

  void newpath();

  void stroke();

  void closepath();

  void setHoja( const std::string& );

  void agregarCalculo( const std::string& );

  void imprimirStack();
};

#endif /* POSTSCRIPT_H_ */
