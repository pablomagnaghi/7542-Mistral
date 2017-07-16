#ifndef _DOC_TEMPLATE_H_INCLUDED_
#define _DOC_TEMPLATE_H_INCLUDED_

#include "XmlNodo.h"
#include "Template.h"
#include "Fecha.h"

#include <string>
#include <vector>

  // Clase que representa un documento con diferentes versiones de Templates.
  // Si se abre en solo lectura los cambios no se guarda al cerrarse.
  // Permite acceder a las versiones en forma secuencial o por fecha.

class DocTemplate {
private:
  bool docValido;
  std::string nombre;
  std::string descripcion;
  std::string xpathNodoDatos;

  bool soloLectura;
  std::vector<Template*> misTemplates;

  // Genera el xml que representa al documento.

  XmlNodo toXml();

public:

  // Abre un archivo xml, y carga los distintos templates e información
  //  que contenga.Si se abre en solo lectura, no se persiste al cerrar el
  //  documento.
  DocTemplate( const std::string& path );


  // Crea un nuevo documento a partir del path si es que este no existe.
  // Por default lo abre para lectura y escritura.
  DocTemplate(  const std::string& nombre, const std::string& descripcion,
		const std::string& xpathNodoDatos );
  
  virtual ~DocTemplate();

  // Devuelve true si se logró abrir y cargar el documento.
  bool isOpen() const;


  // Guarda el DocTemplate si es que se no se abrió en modo de soloLectura.
  // Utiliza el método privado toXml()::Xmlodo*
  void saveAs( const std::string& path );


  // Devuelve un template en el cual la fecha pasada por parámetro pertenezca
  // al período de válidez del template.Si hay varios devuelve el primero.
  // NULL si no existe un template que cumpla con el requisito.
  Template* getVersion( Fecha& f );


  // Devuelve el primer Template de la lista.NULL si no existe ninguna versión-
  Template* getVersion( unsigned int num = 0 );


  int getCantidadDeVersiones();

  void agregarVersion( Template* );

  const std::string& getNombre() const;
  void setNombre( const std::string& );

  const std::string& getDescripcion() const;
  void setDescripcion( const std::string& );

  std::string getXpathNodoDatos() const;
  void setXpathNodoDatos( const std::string& );
};

#endif 
