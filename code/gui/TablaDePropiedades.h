#ifndef _TABLA_DE_PROPIEDADES_H_INCLUDED_
#define _TABLA_DE_PROPIEDADES_H_INCLUDED_

#include <gtkmm.h>

#include "ObjetoConAtributos.h"
#include "FormatoAtributo.h"
#include "TipoAtributo.h"
#include "ObjetoGui.h"

#include "./../ObjetoGrafico.h"
#include "./../Visitor.h"
#include "./../XmlNodo.h"

class ObjetoGraficoBasico : public ObjetoGrafico {
public:
  ObjetoGraficoBasico() {
  }

  void accept( Visitor* v ) {
  }
  XmlNodo toXml() {
    XmlNodo vacio;
    return vacio;
  }
};


class ObjetoConAtributosBasicos : public ObjetoGui {
public:
  ObjetoConAtributosBasicos()
  : ObjetoGui( new ObjetoGraficoBasico() ) {
  }
};

class TablaDePropiedades : public Gtk::HBox {
private:

  Gtk::Entry entryNull1;
  Gtk::Entry entryNull2;
  Gtk::VBox boxNull;

  ObjetoConAtributos* obj;
  ObjetoConAtributosBasicos objnull;

  std::list<TipoAtributo*> atributosEnLista;

  void crearAtributos( std::list<TipoAtributo*>&, const std::list<FormatoAtributo>&,
		       ObjetoConAtributos* );
  void clear();
  void cargarLista();
public:
  TablaDePropiedades();
  void setObjeto( ObjetoConAtributos* obj );
  ~TablaDePropiedades();
};

#endif
