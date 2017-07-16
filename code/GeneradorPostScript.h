#ifndef GENERADORPOSTSCRIPT_H_
#define GENERADORPOSTSCRIPT_H_

#include "DocTemplate.h"
#include "Xml.h"
#include "VisitorPostScript.h"

#include <string>
#include <sstream>
#include <iostream>

class GeneradorPostScript {
private:
  Template* miTemplate;
  Xml* xmlDatos;
  std::string path;
  std::string tagDeDatos;

  // codigo opcional para generar un solo archivo postScript
  // con todas las facturas

  void inicializarUnicoArchivo( std::ofstream& archivo );
  void newPage( std::ofstream&, int );
  void generarUnicoArchivo( XmlNodeSet& );
  void generarVariosArchivos( XmlNodeSet& );

public:
  GeneradorPostScript( Template* version, Xml* xmlDatos, const std::string& tagDeDatos );
  virtual ~GeneradorPostScript();

  bool procesar( bool );
};

#endif /* GENERADORPOSTSCRIPT_H_ */
