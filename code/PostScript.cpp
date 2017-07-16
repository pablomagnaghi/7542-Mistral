#include "PostScript.h"
#include <sstream>

PostScript::PostScript( std::ostream& archivo )
: archivo(archivo) {
}

PostScript::~PostScript() {
  archivo << std::endl;
}

void PostScript::moveto( int posX, int posY ) {
  archivo << posX << " " << posY << " moveto % posX posY" << std::endl;
}

// si el color es menor a MAXCOLOR se devuelve un string que contiene
// "0.numero de color" si el color es el maximo se devuelve un string
// de valor "1". En PostSript los valores de color van de 0 a 1 !!!!!!!!
// 0 0 0 es el negro y 1 1 1 es el blanco
std::string PostScript::getColor( int color ) {
  std::stringstream buf;
  buf << color;

  if (color != MAXCOLOR)
    return 	"0." + buf.str();
  else return "1";
}

void PostScript::setrgbcolor( int cR, int cV, int cA ) {
  archivo << getColor(cR) << " " << getColor(cV) << " ";
  archivo << getColor(cA) << " setrgbcolor" << std::endl;
}

void PostScript::rlineto(int posX, int posY) {
  archivo << posX << " " << posY << " rlineto" << std::endl;
}

void PostScript::lineto( int posX, int posY ) {
  archivo << posX << " " << posY << " lineto" << std::endl;
}

void PostScript::setlinewidth( int borde ) {
  archivo << borde << " setlinewidth" << std::endl;
}

void PostScript::fill() {
  archivo << "gsave" << std::endl;
  this->setrgbcolor(MAXCOLOR, MAXCOLOR, MAXCOLOR);
  archivo << "fill" << std::endl;
  archivo << "grestore" << std::endl;
}

// defino el procedimiento para darle borde al texto
void PostScript::bordear( int posX, int posY, int cR, int cV, int cA, int borde, int ancho, int alto ) {
  archivo << "/celda {" << std::endl;
  this->crearRecuadro( posX, posY, cR, cV, cA, borde, ancho, alto );
  archivo << "} def" << std::endl;
  archivo << std::endl;
}


void PostScript::definirVariables( int posX, int posY, int distancia, int ancho, int alto, int borde  ) {
  archivo << "/LM " << posX + borde << " def % defino margen izquierdo" << std::endl;
  archivo << "/RM " << posX + ancho - borde << " def % defino margen derecho" << std::endl;
  archivo << "/ypos " << posY + alto - distancia << " def % actual posY" << std::endl;
  archivo << "/lineheight " << distancia << " def % distancia entre lineas" << std::endl;
  archivo << "/posFinal " << posY + distancia << " def %posY + size" << std::endl;
  archivo << std::endl;
}

// procedimiento que es llamado cuando el texto excede el tamaño del area que
// se le asigno
void PostScript::truncarTexto( int posX, int posY, int size, int ancho ) {
  archivo << "/borrar {" << std::endl;
  this->newpath();
  this->moveto( posX, posY );
  this->rlineto( 0, size );
  this->rlineto( ancho, 0 );
  this->rlineto( 0, -size);
  this->rlineto( -ancho, 0);
  this->closepath();
  this->fill();
  archivo << "celda } def" << std::endl;
}


// defino el procedimiento para pasar a la linea siguiente
// cuando todavia hay espacio y texto para escribir
void PostScript::newline() {
  archivo << "/newline %move to next line" << std::endl;
  archivo << "{ ypos lineheight sub %decrease ypos" << std::endl;
  archivo << "/ypos exch def %...& save new value" << std::endl;
  archivo << "LM ypos moveto } def %move to next line" << std::endl;
  archivo << std::endl;
}

void PostScript::prtstr() {
  archivo << "/prtstr %stack: str" << std::endl;
  archivo << "{ ypos posFinal gt {" << std::endl;
  archivo << "dup stringwidth pop" << std::endl;
  archivo << "currentpoint pop" << std::endl;
  archivo << "add RM gt %sum > right margin?" << std::endl;
  archivo << "{newline} if" << std::endl;
  archivo << "show } { borrar } ifelse } def" << std::endl;
  archivo << std::endl;
}

// le agrego a cada palabra el procedimiento en PostScript
// para saber si me paso de la longitud
void PostScript::escritura (const std::string& texto) {
  unsigned int i = 0, j = 0;
  std::string palabra = "";

  archivo << "/escritura {" << std::endl;
  while (i < texto.size()) {
	palabra += texto[i];
	if (texto[i] == ' ') {
	  archivo << "(" << palabra << ") prtstr ";
	  palabra.clear();
	}
	i++;
	// para no escribir todo en una sola linea
	j++;
	if (j == LIM) {
	  archivo << std::endl;
	  j = 0;
	}
  }
  archivo << "} def" << std::endl;
  archivo << std::endl;
}

void PostScript::setfont( int size, const std::string& tipoFuente ) {
  archivo << "/" << tipoFuente << " findfont" << std::endl;
  archivo << size << " scalefont setfont" << std::endl;
  archivo << std::endl;
}

void PostScript::main( int cR, int cV, int cA ) {
  archivo << "celda" << std::endl;
  archivo << "LM ypos moveto" << std::endl;
  this->setrgbcolor( cR, cV, cA );
  archivo << "escritura" << std::endl;
  archivo << "clear" << std::endl;
}

void PostScript::ptr() {
  // creo funcion para imprimir numero del stack de hasta 4 posiciones
  archivo << "/nstr 100 string def" << std::endl;
  archivo << "/prt-n % stack: n" << std::endl;
  archivo << "{ nstr cvs show } def" << std::endl;
}

void PostScript::crearRecuadro( int posX, int posY, int cR, int cV, int cA, int borde,
		int ancho, int alto ) {
  this->newpath();
  this->moveto( posX, posY );
  this->rlineto( 0, alto);
  this->rlineto( ancho, 0);
  this->rlineto( 0, -alto);
  this->rlineto( -ancho, 0);
  this->closepath();
  this->setlinewidth( borde );
  if (borde) {
	this->setrgbcolor( cR, cV, cA );
	this->stroke();
  }
  else {
    this->setrgbcolor( MAXCOLOR, MAXCOLOR, MAXCOLOR );
    this->stroke();
    this->setrgbcolor( cR, cV, cA );
  }
  archivo << std::endl;
}

void PostScript::newpath() {
  archivo << "newpath" << std::endl;
}

void PostScript::stroke() {
  archivo << "stroke" << std::endl;
}

void PostScript::closepath() {
  archivo << "closepath" << std::endl;
}

void PostScript::setHoja( const std::string& tipoHoja) {
  archivo << tipoHoja << std::endl;
}

void PostScript::agregarCalculo( const std::string& elementoDeCalculo ) {
  archivo << elementoDeCalculo << " ";
}

void PostScript::imprimirStack() {
  // Imprimo numero del stack
  archivo << std::endl;
  archivo << "prt-n" << std::endl;
  archivo << "clear" << std::endl;
}
