#ifndef PETICIONHTTP_H_
#define PETICIONHTTP_H_


#include <iostream>
#include <string>
#include <map>

#include "common_MensajeHTTP.h"

// Metodos que puede tener una peticion
#define METODO_POST	"POST"
#define METODO_HEAD	"HEAD"
#define METODO_GET 	"GET"

#define FINAL "\r\n\r\n"

class PeticionHTTP : public MensajeHTTP {
private:
  std::string version;
  std::string metodo;
  std::string path;

public:
  PeticionHTTP( const std::string& peticion );
  PeticionHTTP( const std::string& tipo, 
		const std::string& path,
		const std::string& version );


  std::string getTipoPeticion() const;
  void setTipoPeticion( std::string );
  
  std::string getVersion() const;
  void setVersion( std::string );


  std::string getPath() const;
  void setPath( std::string );


  std::string obtenerContentType()const ;
  std::string obtenerContentLenght()const ;

  std::string& toString( std::string& str ) const;

};

#endif /* PETICIONHTTP_H_ */
