#ifndef _CONTEXTO_EDITOR_H_INCLUDED_
#define _CONTEXTO_EDITOR_H_INCLUDED_

#include "./../DocTemplate.h"
#include "./../Template.h"

#include "Observable.h"

#include <string>

class ContextoEditor : public Observable {
private:
  DocTemplate* docTemplate;
  Template* versionDeTrabajo;
  std::string pathTemplate;

public:
  /*
   * Inciializa un contexto sin documnto y sin version de trabajo
   **/
  ContextoEditor();

  DocTemplate* getDocumento();
  Template* getVersionDeTrabajo();

  bool tieneDocumento() const;
  bool tieneVersionDeTrabajo() const;
  const bool tieneArchivo() const;
  const std::string& getPath() const;

  /*
   * Crea un nuevo documento  y lo setea como el actual.
   * Libera la memoria del doc actual si es que había.
   **/
  bool newDocumento( DocTemplate* documento );

  /*
   * Agrega una nueva version al documento.
   * y la setea como version de trabajo actual
   **/
  bool newVersion( Template* );

  /*
   * Intenta abrir un nuevo documento y setearlo en el contexto
   * Si el path no exite o es inválido devuelve false y el documento del contexto
   * no se modifica.
   **/
  bool openDocumento( const std::string path );

  /*
   * Cambia la version de trabajo actual,
   * Devuelve false si no existe una version cono ese numero.
   **/
  bool seleccionarVersionDeTrabajo( unsigned int numVersion );

  /*
   * Libera la memoria del Documento y deja el ContextoEditor vacío.
   **/
  void close();

  /*
   * Guarda el DocTemplate en su archivo
   **/
  bool save();

  /*
   * Guarda el DocTemplate en en otro archivo.Mantiene la version seleccionada
   **/
  bool saveAs( const std::string& nuevoPath );
  
};

#endif