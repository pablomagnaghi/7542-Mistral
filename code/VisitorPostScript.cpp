#include "VisitorPostScript.h"

#include "Linea.h"
#include "TextoFijo.h"
#include "TextoVariable.h"
#include "Calculo.h"
#include "ObjetoLista.h"
#include "Columna.h"
#include <iostream>
#include <list>
#include <iostream>

#include "Xml.h"

VisitorPostScript::VisitorPostScript( Xml* docXml, std::ostream& psFile1, 
		std::ostream& logFile )
:  psFile(psFile1),  logFile(logFile), ps(psFile1 ) {
    docDeDatos = docXml;
    tieneXmlDeDatos = docXml->valido();
    if ( tieneXmlDeDatos )
      tieneXmlDeDatos = docXml->tieneContextoXpath();
    if ( !tieneXmlDeDatos )
      mensajeToLogFile("El archivo de datos es incorreto o no "
    		  "tiene contexto xpath inicializado\n", false );
}

VisitorPostScript::VisitorPostScript() 
: psFile( std::cout ), logFile( std::cerr), ps( std::cout ) {
  docDeDatos = NULL;
  this->tieneXmlDeDatos = false;
}

std::string VisitorPostScript::getStringFromInt (int num) {
  std::stringstream buf;
  buf << num;
  return buf.str();
}

bool VisitorPostScript::esOperador( const std::string& c ) {
  return ( c == "add" || c == "sub" || c == "div" || c == "mul"  );
}

// metodo usado en el visit( Calculo& )
// obtiene la lista final que contiene todos los valores para el calculo
// si al obtener un valor con xpath se produce un error se devuelve false
bool VisitorPostScript::xpathsCorrectos( Calculo& c, std::list<std::string>& calculo ) {
  bool xpathCorrecto = true;

  std::list<ElementoDeCalculo*>::iterator it = c.listaBegin();

  while ( ( it != c.listaEnd() ) && ( xpathCorrecto ) ) {
	  if ( (*it)->getContenido().size() ) {
	    if ( !( esOperador( (*it)->getContenido() ) ) ) {
	      // es un operando variable, busco su valor con xpath
	      XmlNodo nodo;
	      XmlNodeSet nodeSet = docDeDatos->evaluarExpresion( (*it)->getContenido() );
	      if ( nodeSet.size() == UNO ) {
	    	nodo = nodeSet.getNodo( 0 );
	    	calculo.push_back( nodo.getContenido() ) ;
	      } else {
	    	  mensajeToLogFile("No se puede resolver consulta en archivo de datos para operando\n");
	    	  xpathCorrecto = false;
	      }
	    } else calculo.push_back( (*it)->getContenido() );
	  } else calculo.push_back( getStringFromInt( (*it)->getValor( NULL ) ) );

	  it++;
  }

  return xpathCorrecto;
}

void VisitorPostScript::visit( Hoja& h ) {
  ps.setHoja( h.getTipoHoja() );
  ps.crearRecuadro( h.getPosX(), h.getPosY(), h.getColorRojo(), h.getColorVerde(),
		  h.getColorAzul(), h.getBorde(), h.getAncho(), h.getAlto() );

  std::list<ObjetoGrafico*>::iterator it = h.listaBegin();
  while ( it != h.listaEnd() ) {
    (*it)->accept( this );
    it++;
  }
}

// dibuja una linea (horizontal, vertical u oblicua) en codigo postscript
// todos los comandos se separan con caracter de espacio
void VisitorPostScript::visit( Linea& l ) {
  ps.moveto( l.getPosX(), l.getPosY() );
  ps.setrgbcolor( l.getColorRojo(), l.getColorVerde(), l.getColorAzul() );
  ps.lineto( l.getPosXfinal(), l.getPosYfinal() );
  ps.setlinewidth( l.getBorde() );
  ps.stroke();
}

// dibuja un texto fijo en codigo postscript
// eligiendo tamaño, color y tipo de letra
// todos los comandos se separan con caracter de espacio
void VisitorPostScript::visit( TextoFijo& tf ) {

  ps.bordear( tf.getPosX(), tf.getPosY(), tf.getColorRojo(), tf.getColorVerde(), tf.getColorAzul(),
		  tf.getBorde(), tf.getAncho(), tf.getAlto() );

  ps.definirVariables( tf.getPosX(), tf.getPosY(), tf.getSize(), tf.getAncho(), tf.getAlto(), tf.getBorde() );
  ps.truncarTexto( tf.getPosX(), tf.getPosY(), tf.getSize(), tf.getAncho() );
  ps.newline();
  ps.prtstr();
  ps.escritura( tf.getTexto() + " ");
  ps.setfont( tf.getSize(), tf.getTipoFuente() );
  ps.main( tf.getColorRojo(), tf.getColorVerde(), tf.getColorAzul() );
}

void VisitorPostScript::visit( TextoVariable& tv ) {
  if ( tieneXmlDeDatos ) {
    // primero busco si esta el dato en el xpath
    XmlNodo nodo;

    XmlNodeSet nodeSet = docDeDatos->evaluarExpresion( tv.getTextoXpath() );

    if ( nodeSet.size() == UNO ) {
      nodo = nodeSet.getNodo( 0 );

      ps.bordear( tv.getPosX(), tv.getPosY(), tv.getColorRojo(), tv.getColorVerde(), tv.getColorAzul(),
    		  tv.getBorde(), tv.getAncho(), tv.getAlto() );


      ps.definirVariables(  tv.getPosX(), tv.getPosY(), tv.getSize(), tv.getAncho(), tv.getAlto(), tv.getBorde() );
      ps.truncarTexto( tv.getPosX(), tv.getPosY(), tv.getSize(), tv.getAncho() );
      ps.newline();
      ps.prtstr();
      ps.escritura( nodo.getContenido() + " ");

      ps.setfont( tv.getSize(), tv.getTipoFuente() );

      ps.main( tv.getColorRojo(), tv.getColorVerde(), tv.getColorAzul() );
    } 
    else
      mensajeToLogFile("No se puede resolver consulta en archivo de datos para texto variable\n");
  }
  else 
    mensajeToLogFile("No existe un archivo de datos para el texto variable\n");
}

// si cantidad de operandos = cantidad de operadores + 1 se realiza el calculo
// eso se controla en cantidadCorrecta
void VisitorPostScript::visit( Calculo& c ) {
  std::list<std::string> calculo;

  if ( c.cantidadCorrecta() ) {

	  if ( xpathsCorrectos( c, calculo ) ) {
		ps.crearRecuadro( c.getPosX(), c.getPosY(), c.getColorRojo(), c.getColorVerde(),
			c.getColorAzul(), c.getBorde(), c.getAncho(), c.getAlto() );
		ps.moveto( c.getPosX() + c.getBorde(), c.getPosY() + c.getAlto() - c.getSize() );

		ps.setfont( c.getSize(), c.getTipoFuente() );
		ps.ptr();

		std::list<std::string>::iterator it = calculo.begin();

		while ( it != calculo.end() ) {
		  ps.agregarCalculo( (*it) );
		  it++;
		}

		ps.imprimirStack();
	  } else mensajeToLogFile("No se puede realizar calculo, xpath incorrecto\n");

	} else mensajeToLogFile("No se puede realizar calculo, cantidad incorrecta de "
			"operandos u operadores ( hay mas de los necesarios)\n");

}

void VisitorPostScript::dibujarEncabezado( ObjetoLista& l) {
  std::list<Columna*>::iterator it = l.columnasBegin();

  while ( it != l.columnasEnd() ) {
	TextoFijo* obj = (*it)->getEncabezado();
	obj->accept( this );
	it++;
  }
}

void VisitorPostScript::dibujarAdicionales( ObjetoLista& l, int pos) {
  int altoAux = altoLista;

  std::list<Columna*>::iterator it = l.columnasBegin();

  if ( altoLista <= l.getAlto() ) {
	while ( it != l.columnasEnd() ) {
	  std::list<Texto*>::iterator itAdicionales = (*it)->listaBegin(pos );
	  altoLista = altoAux + (*itAdicionales)->getAlto();
	  while ( ( itAdicionales != (*it)->listaEnd() ) && ( altoLista <= l.getAlto() ) ) {
		(*itAdicionales)->accept( this );
		itAdicionales++;
		altoLista += (*itAdicionales)->getAlto();
	  }
	  it++;
	}
  }
}

void VisitorPostScript::visit( ObjetoLista& l ) {
  altoLista = 0;

  XmlNodo nodoAnterior = docDeDatos->getCurrentNodo();
  // cada vez que se va a agregar una fila se revisa si se
  // paso el alto que tenia la lista

  // primero dibujo el encabezado
  this->dibujarEncabezado( l );

  std::list<Columna*>::iterator it = l.columnasBegin();

  XmlNodeSet nodeSet = docDeDatos->evaluarExpresion( l.getXpath() );
  XmlNodo nodo;
  int pos = 0;

  // dibujo el cuerpo de la lista
  // los nodos representan las filas

  while ( pos < nodeSet.size() ) {
    nodo = nodeSet.getNodo( pos );

    docDeDatos->setCurrentNode( nodo );

    it = l.columnasBegin();
    altoLista += (*it)->getEncabezado()->getAlto();

    if ( altoLista <= l.getAlto() ) {
      while ( it != l.columnasEnd() ) {
    	(*it)->getCuerpo( pos )->accept( this );
    	it++;
      }
    }

    pos++;
  }

  // dibujo las celdas adicionales
  docDeDatos->setCurrentNode( nodoAnterior );

  this->dibujarAdicionales( l, pos );
}

void VisitorPostScript::mensajeToLogFile( const std::string& msj, bool error ) {
  std::string msjCompleto;
  msjCompleto += '\t';

  if ( error )
    msjCompleto = "ERROR: ";
  else
    msjCompleto = "WARNING: ";

  msjCompleto += msj;

  this->logFile << std::endl << msjCompleto;
}

