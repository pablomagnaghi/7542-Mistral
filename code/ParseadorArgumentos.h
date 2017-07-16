#ifndef PARSEADORARGUMENTOS_H_
#define PARSEADORARGUMENTOS_H_

#include <iostream>
#include <string>
#include <sstream>

#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4
#define CINCO 5
#define SEIS 6

#define EN_LINEA "-s"
#define LOTE "-l"
#define CODIGO_OPCIONAL "-u"

class ParseadorArgumentos {
private:
  bool error;
  bool esModoEnLinea;
  bool esModoLote;
  bool enUnicoArchivo;
  int puerto;

  void obtenerPuerto( const std::string& );
  void obtenerPrimerArgumento( const std::string&, int, char** );
  void obtenerArgumentoAdicional ( const std::string& );
public:
  ParseadorArgumentos();
  virtual ~ParseadorArgumentos();

  void parsear( int argc, char** argv );

  bool getError();
  bool getEsModoEnLinea();
  bool getEsModoLote();
  bool getEnUnicoArchivo();

  int getPuerto();

  void help();
};

#endif /* PARSEADORARGUMENTOS_H_ */
