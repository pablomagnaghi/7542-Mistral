#include "ParseadorArgumentos.h"

ParseadorArgumentos::ParseadorArgumentos() {
  this->error = false;
  this->esModoEnLinea = false;
  this->esModoLote = false;
  this->enUnicoArchivo = false;
}

ParseadorArgumentos::~ParseadorArgumentos() {

}

void ParseadorArgumentos::obtenerPuerto( const std::string& cadena ) {
  std::stringstream buffer(cadena);
  buffer >> this->puerto;
}

void ParseadorArgumentos::obtenerPrimerArgumento( const std::string& modo, int argc, char** argv) {
  if ( ( modo == EN_LINEA ) && ( argc == TRES ) ) {
	std::cout << "Modo linea" << std::endl;
	std::cout << "Presionar 'q' para finalizar servidor" << std::endl;
	esModoEnLinea = true;
	obtenerPuerto( argv[DOS] );
  } else if ( ( modo == LOTE ) && ( ( argc == CINCO ) || ( argc == SEIS ) ) ) {
	  std::cout << "Modo lote" << std::endl;
	  esModoLote = true;
  } else error = true;
}

// controlo si se pide la opcion de unico archivo
void ParseadorArgumentos::obtenerArgumentoAdicional ( const std::string& codOpc ) {
  if ( codOpc == CODIGO_OPCIONAL )
	enUnicoArchivo = true;
  else error = true;
}

void ParseadorArgumentos::parsear( int argc, char** argv ) {
  if ( argc > UNO ) {
    obtenerPrimerArgumento( argv[UNO], argc, argv );
    if ( ( !error ) && ( argc == SEIS ) )
	  obtenerArgumentoAdicional( argv[CINCO] );
  } else this->error = true;
}

bool ParseadorArgumentos::getError() {
  return this->error;
}

bool ParseadorArgumentos::getEsModoEnLinea() {
  return this->esModoEnLinea;
}

bool ParseadorArgumentos::getEsModoLote() {
  return this->esModoLote;
}

bool ParseadorArgumentos::getEnUnicoArchivo() {
  return this->enUnicoArchivo;
}

int ParseadorArgumentos::getPuerto() {
  return this->puerto;
}

void ParseadorArgumentos::help() {
  std::cout << "Crear desde linea en unico archivo, parametro opcional: -u" << std::endl;
  std::cout << "Formato de fecha:: dd/mm/aaaa" << std::endl;
  std::cout << "Modo lote o batch: ./psPorLote -l <template-path> "
		  "<datos-path> <fecha> <opcional -u>" << std::endl;
  std::cout << "Modo en linea: ./psPorLote -s <puerto>" << std::endl;
}

