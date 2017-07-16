#include "ContextoEditor.h"

#include "./../DocTemplate.h"
#include "./../Template.h"
#include "./../Exceptions.h"

#include <string>

/*
 * Inciializa un contexto sin documnto y sin version de trabajo
 **/
ContextoEditor::ContextoEditor() {
  docTemplate = NULL;
  versionDeTrabajo = NULL;
  this->close();
}

DocTemplate* ContextoEditor::getDocumento() {
  return docTemplate;
}

Template* ContextoEditor::getVersionDeTrabajo() {
  return versionDeTrabajo;
}


bool ContextoEditor::tieneDocumento() const {
  return ( docTemplate != NULL );
}

bool ContextoEditor::tieneVersionDeTrabajo() const {
  return (versionDeTrabajo != NULL);
}

const std::string& ContextoEditor::getPath() const {
  return pathTemplate;
}

const bool ContextoEditor::tieneArchivo() const {
  return ( pathTemplate != "" );
}

/*
 * Crea un nuevo documento en el archivo y lo setea como el actual.
 * Libera la memoria del doc actual si es que había.
 * Devuelve false si el path pasado por parametro es inválido.
 **/
bool ContextoEditor::newDocumento( DocTemplate* documento ) {

  this->close();
  this->docTemplate = documento;
  this->versionDeTrabajo = NULL;
  this->notifyObservadores();
  
  return true;
}

/*
 * Agrega una nueva version al documento.
 * y la setea como version de trabajo actual
 **/
bool ContextoEditor::newVersion( Template* nuevaVersion ) {
  if ( (docTemplate) && (nuevaVersion) ) {
    docTemplate->agregarVersion( nuevaVersion );
    seleccionarVersionDeTrabajo( docTemplate->getCantidadDeVersiones()-1 );
  }
  return ( nuevaVersion != NULL );
}

/*
 * Intenta abrir un nuevo documento y setearlo en el contexto
 * Si el path no exite o es inválido devuelve false y el documento del contexto
 * no se modifica.
 **/
bool ContextoEditor::openDocumento( const std::string path ) {
  bool resultado = true;

  try {
    DocTemplate* nuevoDoc = new DocTemplate( path );
    this->close();
    this->pathTemplate = path;
    this->docTemplate = nuevoDoc;
    this->seleccionarVersionDeTrabajo( 0 );
    this->notifyObservadores();
  }
  catch ( Exception* ex ) {
    resultado = false;
    std::cout << ex->getMsjError();
    delete ex;
  }

  return resultado;
}

/*
 * Cambia la version de trabajo actual,
 * Devuelve false si no existe una version cono ese numero.
 **/
bool ContextoEditor::seleccionarVersionDeTrabajo( unsigned int numVersion ) {
  bool resultado = false;

  if ( docTemplate ) {
    int cantVersiones = docTemplate->getCantidadDeVersiones();
    if ( numVersion < (unsigned int)cantVersiones ) {
      versionDeTrabajo = docTemplate->getVersion( numVersion );
      resultado = true;
      this->notifyObservadores();
    }
  }
  return resultado;
}

  
/*
 * Libera la memoria del Documento y deja el ContextoEditor vacío.
 **/
void ContextoEditor::close() {
  if ( docTemplate ) {
    delete docTemplate;
  }
  docTemplate = NULL;
  versionDeTrabajo = NULL;
  pathTemplate = "";
  this->notifyObservadores();
}


/*
 * Guarda el DocTemplate en su archivo
 **/
bool ContextoEditor::save() {
  if ( (docTemplate) && (tieneArchivo()) ) {
    docTemplate->saveAs( pathTemplate );
  }
  return ( (docTemplate) && (tieneArchivo()) );
}

bool ContextoEditor::saveAs( const std::string& nuevoPath ) {
  bool resultado = true;
  try {
    this->docTemplate->saveAs( nuevoPath );
    this->pathTemplate = nuevoPath;
  }
  catch ( Exception* ex ) {
    resultado = false;
    std::cout << ex->getMsjError();
    delete ex;
  }
  return resultado;
}

  