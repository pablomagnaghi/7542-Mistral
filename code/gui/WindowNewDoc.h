#ifndef _WINDOW_NEW_DOC_H_INCLUDED_
#define _WINDOW_NEW_DOC_H_INCLUDED_

#include <gtkmm.h>
#include <string>

#include "./../DocTemplate.h"

#define DEFAULT_NOMBRE_DOC	"facturas"
#define DEFAULT_DESCRIPCION_DOC	"facturas de luz"
#define DEFAULT_TAG		"Factura"

#define LABEL_NOMBRE_DOC	"Nombre:"
#define LABEL_DESCRIPCION_DOC	"Descripcion de la plantilla:"
#define LABEL_TAG		"Tag de datos:"

#define TITULO_NEW_DOC		"Nueva plantilla"
#define TITULO_PROPIEDADES_DOC 	"Propiedades de plantilla"
class WindowNewDoc : public Gtk::Dialog {
private:
  Gtk::HBox boxNombre;
  Gtk::Label labelNombre;
  Gtk::Entry entryNombre;

  Gtk::HBox boxDescripcion;
  Gtk::Label labelDescripcion;
  Gtk::Entry entryDescripcion;

  Gtk::HBox boxTag;
  Gtk::Label labelTag;
  Gtk::Entry entryTag;

  void init( const std::string& nombre, 
		const std::string& desc, 
		const std::string& tag );
public:
  WindowNewDoc( DocTemplate& );

  WindowNewDoc( const std::string& nombre, 
		const std::string& desc, 
		const std::string& tag );
  WindowNewDoc();
  ~WindowNewDoc();

  std::string getNombre() const;
  std::string getDescripcion() const;
  std::string getTag() const;

};

#endif
