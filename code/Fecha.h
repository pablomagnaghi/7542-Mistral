#ifndef _FECHA_H_INCLUDED_
#define _FECHA_H_INCLUDED_

#define DIA_DEFAULT	25
#define MES_DEFAULT	12
#define ANNIO_DEFAULT 2010

// cuando se crea una fecha con el constructor por defecto sus atributos
// dia, mes y annio se inicializan con MAXF_FECHA que representa una fecha que
// no tiene limite, una fecha "hasta siempre"

#define MAX_FECHA 10000
#define FECHA 10
#define POS 2
#define POS_ANNIO 4
#define MAX_DIA 31
#define DICIEMBRE 12

#include <iostream>
#include <string>
#include <sstream>

class Fecha {
private:
  int dia;
  int mes;
  int annio;
  std::string fecha;

  void revisarFecha();
  void crearFechaInvalida();
  void obtenerCampos();

public:
  Fecha();
  Fecha( int dia, int mes, int annio );
  Fecha( const std::string& );
  
  bool pertenece( const Fecha& fechaInicial, const Fecha& fechaFinal ) const;

  bool esValida() const;
  bool operator>( const Fecha& ) const;

  int getDia() const;
  void setDia( int dia );

  int getMes() const;
  void setMes( int mes );

  int getAnnio() const;
  void setAnnio( int annio );

  friend std::ostream& operator<<( std::ostream&, const Fecha& );
};

#endif
