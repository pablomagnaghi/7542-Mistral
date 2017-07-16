#include "Xml.h"
#include "XmlNodo.h"

#include "Template.h"
#include "DocTemplate.h"
#include "Exceptions.h"
#include "GeneradorPostScript.h"
#include "Fecha.h"

#include "ParseadorArgumentos.h"

#include "VisitorPostScript.h"
#include <iostream>
#include <string>
#include <sstream>

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "XmlNodeSet.h"

#include "./servidor/server_Server.h"

#define CHAR_EXIT_SERVER	'q'

int main ( int argc, char** argv ) {
  ParseadorArgumentos parseador;

  parseador.parsear( argc, argv );

  if ( parseador.getError() )
	parseador.help();
  else {
	// Modo servidor
	if ( parseador.getEsModoEnLinea() ) {
	  Server server( parseador.getPuerto() );
	  server.start();

	  if (server.isRunning()) {
		char c;
		do { std::cin >> c; }
		while ((server.isRunning()) && (c!=CHAR_EXIT_SERVER));
	  }

	  server.tryToStop();
	  server.join();
	}

	// Modo por lotes-
	if ( parseador.getEsModoLote() ) {
	  try {
		// Levanto el template y el documento de datos
		DocTemplate docLevantado( argv[DOS] );
		Xml xmlDatos( argv[TRES] );
		std::string tagDeDatos = docLevantado.getXpathNodoDatos();
		Fecha fecha( argv[CUATRO] );

		if ( docLevantado.getVersion( fecha ) ) {
		  GeneradorPostScript generador(  docLevantado.getVersion( fecha ), &xmlDatos, tagDeDatos );
		  generador.procesar( parseador.getEnUnicoArchivo() );
		}
		  else std::cout << "Error: No existe una version para esa fecha" << std::endl;
	  } catch ( DocTemplateInvalidoExc* ex ) {
		  std::cout << std::endl << "Error: La plantilla tiene un formato incorrecto"<< std::endl;
		  delete ex;
	  } catch ( DocTemplateArchivoInexistenteExc* ex ) {
		  std::cout << std::endl << "Error: No existe el archivo de plantilla"<< std::endl;
		  delete ex;
	  } catch ( XmlArchivoInexistenteExc* ex ) {
		  std::cout << std::endl << "Error: No existe el archivo de datos"<< std::endl;
		  delete ex;
	  } catch ( XmlArchivoInvalidoExc* ex ) {
		  std::cout << std::endl << "Error: El archivo de datos no es un Xml valido"<< std::endl;
		  delete ex;
	  } catch ( FechaInvalidaException* ex ) {
		  std::cout << std::endl << "Error: La fecha no tiemne un formato valido"<< std::endl;
		  delete ex;
	  }
	}
  }

  return 0;
}
