#ifndef _COMBO_VERSIONES_H_INCLUDED_
#define _COMBO_VERSIONES_H_INCLUDED_

#include "./../Template.h"
#include "./../DocTemplate.h"
#include "ContextoEditor.h"
#include "Observador.h"

#include <gtkmm.h>
#include <list>

class ComboVersiones : public Gtk::ComboBoxText, public Observador {
private:
  ContextoEditor& contexto;
  bool desabilitar;
public:
  ComboVersiones( ContextoEditor& ctx )
  : contexto(ctx) {
    this->set_title( "Version" );
    this->show();
    desabilitar = false;
  }

  void notify() {
    this->clear();
    int cantVersiones = 0;

    if (  (contexto.tieneDocumento()) && 
	  (contexto.getDocumento()->getCantidadDeVersiones()>0) ) {
	      this->set_sensitive( true );
      cantVersiones = contexto.getDocumento()->getCantidadDeVersiones();
      for ( int i = 0; i < cantVersiones; i++ ) {
	std::string strVersion = contexto.getDocumento()->getVersion(i)->toString();
	this->append_text( strVersion );
  	if ( contexto.getVersionDeTrabajo() == contexto.getDocumento()->getVersion(i) ) {
	  desabilitar = true;
  	  this->set_active( i );
	  desabilitar = false;
	}
      }

    }
    else {
	  desabilitar = true;
	  this->append_text( "PLANTILLA SIN VERSIONES" );
  	  this->set_active( 0 );
	  desabilitar = false;
	  this->set_sensitive( contexto.tieneDocumento() );
    }
  }

  void on_changed() {
    if ( !desabilitar ) {
      if ( contexto.tieneDocumento() ) {
	contexto.seleccionarVersionDeTrabajo( this->get_active_row_number() );
      }
    }
  }
  
};

#endif