#include "WindowNewDoc.h"

#include <gtkmm.h>

WindowNewDoc::WindowNewDoc( const std::string& nombre, 
			    const std::string& desc, 
			    const std::string& tag )
: labelNombre(LABEL_NOMBRE_DOC), labelDescripcion(LABEL_DESCRIPCION_DOC),
  labelTag(LABEL_TAG) {
  this->init( nombre, desc, tag );
}
  
WindowNewDoc::WindowNewDoc( DocTemplate& doc )
: labelNombre(LABEL_NOMBRE_DOC), labelDescripcion(LABEL_DESCRIPCION_DOC),
  labelTag(LABEL_TAG) {
  this->init( doc.getNombre(), doc.getDescripcion(), doc.getXpathNodoDatos() );
  this->set_title(TITULO_PROPIEDADES_DOC);
}


WindowNewDoc::WindowNewDoc()
: labelNombre(LABEL_NOMBRE_DOC), 
  labelDescripcion(LABEL_DESCRIPCION_DOC),
  labelTag(LABEL_TAG) {
  this->init(DEFAULT_NOMBRE_DOC,DEFAULT_DESCRIPCION_DOC,DEFAULT_TAG);
  this->set_title(TITULO_NEW_DOC);
}

void WindowNewDoc::init( const std::string& nombre, 
		    const std::string& desc, 
		    const std::string& tag ) {
  boxNombre.add( labelNombre );
  boxNombre.add( entryNombre );
  this->get_vbox()->add( boxNombre );

  boxDescripcion.add( labelDescripcion );
  boxDescripcion.add( entryDescripcion );
  this->get_vbox()->add( boxDescripcion );

  boxTag.add( labelTag );
  boxTag.add( entryTag );
  this->get_vbox()->add( boxTag );

  labelTag.show();
  labelDescripcion.show();
  labelNombre.show();
  
  entryTag.show();
  entryDescripcion.show();
  entryNombre.show();

  boxTag.show();
  boxDescripcion.show();
  boxNombre.show();

  this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  entryNombre.set_text( nombre );
  entryDescripcion.set_text( desc );
  entryTag.set_text( tag );


}


WindowNewDoc::~WindowNewDoc() {
}


std::string WindowNewDoc::getNombre() const {
  return this->entryNombre.get_text();
}

std::string WindowNewDoc::getDescripcion() const {
  return this->entryDescripcion.get_text();
}

std::string WindowNewDoc::getTag() const {
  return this->entryTag.get_text();
}


