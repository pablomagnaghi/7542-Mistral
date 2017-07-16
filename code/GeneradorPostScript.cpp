#include "GeneradorPostScript.h"

GeneradorPostScript::GeneradorPostScript( Template* miTemplate, Xml* xmlDatos,
		const std::string& tagDeDatos ) {
  this->miTemplate = miTemplate;
  this->xmlDatos = xmlDatos;
  this->tagDeDatos = tagDeDatos;
}

GeneradorPostScript::~GeneradorPostScript() {

}

// inicializo el archivo para mostrar las paginas en orden ascendente
void GeneradorPostScript::inicializarUnicoArchivo( std::ofstream& archivo ) {
  archivo << "%!PS-Adobe-2.0" << std::endl;
  archivo << "%%PageOrder: Ascend" << std::endl;
  archivo << "%!" << std::endl;
  archivo << std::endl;
}

void GeneradorPostScript::newPage( std::ofstream& archivo, int numPage ) {
  archivo << "%%Page " << numPage << std::endl;
}

void GeneradorPostScript::generarUnicoArchivo( XmlNodeSet& nodosDeDatos ) {
  std::string pathCompleto;
  pathCompleto += tagDeDatos;
  pathCompleto += ".ps";

  // Abro un unico archivo postscript para todos los templates generados

  std::ofstream archivoPostscript( pathCompleto.c_str() );

  inicializarUnicoArchivo( archivoPostscript );

  std::cout << "Generando archivo postscript " << pathCompleto << std::endl;

  for ( int i = 0; i<nodosDeDatos.size() ;i++ ) {
	// Tomo un nodo y lo pongo como nodoActual del contextoXpath
	XmlNodo nodoActual = nodosDeDatos.getNodo( i );
	xmlDatos->setCurrentNode( nodoActual );

	newPage( archivoPostscript, i + 1 );

	// Creo un VisitorPostScript y generoCodigoPostscript de resultado
	VisitorPostScript visitor( xmlDatos, archivoPostscript, std::cerr);
	miTemplate->getHoja()->accept( &visitor );
  }
}

void GeneradorPostScript::generarVariosArchivos( XmlNodeSet& nodosDeDatos ) {
  for ( int i = 0; i<nodosDeDatos.size() ;i++ ) {
	// Tomo un nodo y lo pongo como nodoActual del contextoXpath
	XmlNodo nodoActual = nodosDeDatos.getNodo( i );
	xmlDatos->setCurrentNode( nodoActual );

	// Abro un archivo postscript por cada template generado
	std::stringstream sstr;
	sstr <<  i;
	std::string pathCompleto;
	pathCompleto += tagDeDatos;
	pathCompleto += sstr.str();
	pathCompleto += ".ps";

	std::cout << "Generando archivo postscript " << pathCompleto << std::endl;

	std::ofstream archivoPostscript( pathCompleto.c_str() );

	// Creo un VisitorPostScript y generoCodigoPostscript de resultado
	VisitorPostScript visitor( xmlDatos, archivoPostscript, std::cerr );
	miTemplate->getHoja()->accept( &visitor );
  }
}

bool GeneradorPostScript::procesar( bool archivoPostScriptUnico ) {
  bool resultado = false;

  // creo un contexto Xpath
  xmlDatos->crearContextoXpath();

  // Tomo la raíz, evaluo la expresion buscando nodos para el template
  XmlNodo* raiz = xmlDatos->getNodoRaiz();
  xmlDatos->setCurrentNode( *raiz );

  XmlNodeSet nodosDeDatos = xmlDatos->evaluarExpresion( tagDeDatos );
  resultado = ( nodosDeDatos.size()>0 );
  // Genero documentos postscript por cada nodo
  if ( archivoPostScriptUnico ) {
	generarUnicoArchivo( nodosDeDatos );
  } else generarVariosArchivos( nodosDeDatos );

  return resultado;
}
