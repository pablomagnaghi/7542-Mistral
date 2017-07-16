#ifndef _VISITORPOSTSCRIPT_H_INCLUDED_
#define _VISITORPOSTSCRIPT_H_INCLUDED_

#include "Visitor.h"

#include "Hoja.h"
#include "Linea.h"
#include "TextoFijo.h"
#include "TextoVariable.h"
#include "Calculo.h"
#include "ObjetoLista.h"
#include "OperandoConstante.h"
#include "OperandoVariable.h"

#include "PostScript.h"

#include "Xml.h"
#include "XmlNodo.h"
#include "XmlNodeSet.h"
#include <iostream>
#include <string>
#include <sstream>

// Implementacion concreta de visitor que recibe un tipo de Objeto grafico
// y muestra por salida estándar su código postscript.
// Tiene un documento XML para acceder al xml de datos si es necesario.

// Recibe dos flujos de salida: uno para la salida del codigo postscript del Template 
// y otro para los mensajes de error y avisos.
class VisitorPostScript : public Visitor {
private:

  // Documento preparado para recibir consultas Xpath.

  Xml* docDeDatos;
  bool tieneXmlDeDatos;
  std::ostream& psFile; // archivo postscript
  std::ostream& logFile; // archivo de error
  PostScript ps;

  int altoLista;

  std::string getStringFromInt (int num);
  bool esOperador( const std::string& c );
  bool xpathsCorrectos( Calculo& c, std::list<std::string>& );

  void dibujarEncabezado( ObjetoLista& l);
  void dibujarAdicionales( ObjetoLista& l, int pos);

  void mensajeToLogFile( const std::string&, bool error = true );
public:


  // Genera un archivo postscript tomando los datos del "current node"
  // de docXml.Manda los errores a logFile y el archivo generado a psFile

  VisitorPostScript( Xml* docXml, std::ostream& psFile, std::ostream& logFile );

  // Genera un archivo postscript sin tomar datos deningún xml.
  // Si existe algun objeto que necesite esos datos, imprime un error endif
  // logFile;

  VisitorPostScript();

  void visit ( Hoja& );
  void visit( Linea& );
  void visit( TextoFijo& );
  void visit( TextoVariable& );
  void visit ( Calculo& );
  void visit( ObjetoLista& );
};

#endif
