#include "TablaDePropiedades.h"

#include <gtkmm.h>
#include <glibmm/refptr.h>


#include "ObjetoConAtributos.h"
#include "FormatoAtributo.h"
#include "TipoAtributo.h"

#include "TipoString.h"
#include "TipoInt.h"
#include "TipoBool.h"
#include "TipoColor.h"

using namespace std;
   

TablaDePropiedades::TablaDePropiedades() {
  this->setObjeto( NULL );
  this->show();

  boxNull.pack_start( entryNull1 );
  boxNull.pack_start( entryNull2 );
  entryNull1.hide();
  entryNull2.hide();
}


void TablaDePropiedades::crearAtributos(list<TipoAtributo*>& attrs,                      						const list<FormatoAtributo>& formatos ,
			        ObjetoConAtributos* objeto) {

  list<FormatoAtributo>::const_iterator it = formatos.begin();
  while ( it != formatos.end() ) {

    TipoAtributo* t = NULL;
    switch ( it->getTipo() ) {
      case ATTR_STRING: {
	t = new TipoString( it->getNombre(), objeto );
	break;
      }
      case ATTR_BOOL: {
	t = new TipoBool( it->getNombre(), objeto );
	break;
      }
      case ATTR_INT: {
	t = new TipoInt( it->getNombre(), objeto );
	break;
      }
      case ATTR_COLOR: {
	t = new TipoColor( it->getNombre(), objeto );
	break;
      }
    }
    if ( t != NULL )
      attrs.push_back( t );
    it++;
  }

}

void TablaDePropiedades::clear() {
  this->foreach ( sigc::mem_fun( *this, &Gtk::HBox::remove) );
  list<TipoAtributo*>::iterator it = atributosEnLista.begin();
  while ( it != atributosEnLista.end() ) {
    delete *it;
    it++;
  }
  atributosEnLista.clear();
}



void TablaDePropiedades::setObjeto( ObjetoConAtributos* obj ) {
  if ( obj ) {
    this->obj = obj;
    this->clear();
    std::list<FormatoAtributo> atributos;
    this->obj->getAtributos( atributos );
    this->crearAtributos( atributosEnLista, atributos, obj  );
    this->cargarLista();
    this->show();
    this->set_sensitive(true);
  } else {
      this->clear();
      std::list<FormatoAtributo> atributos;
      objnull.getAtributos( atributos );
      this->crearAtributos( atributosEnLista, atributos, &objnull  );
      this->cargarLista();
      this->show();
      this->set_sensitive(false);
  }
}

void TablaDePropiedades::cargarLista() {
  list<TipoAtributo*>::iterator it = atributosEnLista.begin();

  while ( it != atributosEnLista.end() ) {

    Gtk::VBox* box = Gtk::manage( new Gtk::VBox() );
    box->pack_start( *(*it)->widgetToSetValor(), false, true, 4 );   
    it++;

    if ( it != atributosEnLista.end() ) {
        box->pack_start( *(*it)->widgetToSetValor() );    
	it++;
    }

    box->show();
    this->pack_start( *box );
  }
}

TablaDePropiedades::~TablaDePropiedades() {
  this->clear();
}

