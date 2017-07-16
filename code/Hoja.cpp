#include "Hoja.h"
#include "Visitor.h"
#include "XmlNodo.h"

Hoja::Hoja( int ancho, int alto, const std::string& tipoHoja )
: ObjetoGraficoRectangular( 0, 0, 0, 0, 0, 0, ancho, alto ) {
  this->tipoHoja = tipoHoja;
}

Hoja::Hoja()
: ObjetoGraficoRectangular( 0, 0, 0, 0, 0, 0, MAXANCHO, MAXALTO ) {
  this->tipoHoja = HOJA;
}

Hoja::Hoja( XmlNodo* nodo) {
  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);

  this->obtenerObjetosGraficos(&nodoAux);
}

ObjetoGraficoRectangular* Hoja::clone() {
  return NULL;
}


Hoja::~Hoja() {
  std::list<ObjetoGrafico*>::iterator it = misObjetos.begin();

  while ( it != misObjetos.end() ) {
    delete (*it);
    it++;
  }
  misObjetos.clear();
}

void Hoja::obtenerObjetosGraficos ( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "objetoLista" ) {
	  ObjetoLista* objeto = new ObjetoLista (nodo);
	  this->agregarObjeto(objeto);
	}
	if ( nodo->getNombre() == "linea" ) {
      Linea* objeto = new Linea (nodo);
      this->agregarObjeto(objeto);
	}
	if ( nodo->getNombre() == "textoFijo" )	{
	  TextoFijo* objeto = new TextoFijo (nodo);
	  this->agregarObjeto(objeto);
	}
	if ( nodo->getNombre() == "textoVariable" ) {
	  TextoVariable* objeto = new TextoVariable (nodo);
	  this->agregarObjeto(objeto);
	}
	if ( nodo->getNombre() == "calculo" ) {
	  Calculo* objeto = new Calculo (nodo);
	  this->agregarObjeto(objeto);
	}

	*nodo = nodo->getHermano();
  }
}

void Hoja::agregarAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::agregarAtributos(nodo);

  XmlNodo nodoTipoHoja("tipoHoja");
  nodoTipoHoja.setContenido(this->tipoHoja);
  nodo->agregarHijo(nodoTipoHoja);
}

void Hoja::obtenerAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::obtenerAtributos(nodo);

  this->tipoHoja = nodo->getContenido();
  *nodo = nodo->getHermano();
}

void Hoja::agregarObjeto( ObjetoGrafico* obj ) {
  this->misObjetos.push_back( obj );
}

void Hoja::removeObjeto( ObjetoGrafico*  obj ) {
  misObjetos.remove( obj );
}

std::list<ObjetoGrafico*>::iterator Hoja::listaBegin() {
  return misObjetos.begin();
}

std::list<ObjetoGrafico*>::iterator Hoja::listaEnd() {
  return misObjetos.end();
}

void Hoja::accept( Visitor* v ) {
  v->visit( *this );
}

std::string Hoja::getTipoHoja() const {
  return this->tipoHoja;
}

void Hoja::setTipoHoja( const std::string& tipoHoja ) {
  this->tipoHoja = tipoHoja;
}

XmlNodo Hoja::toXml() {
  XmlNodo nodo("hoja");

  this->agregarPropiedades(&nodo);
  this->agregarAtributos(&nodo);

  std::list<ObjetoGrafico*>::iterator i;

  for(i = this->listaBegin(); i != this->listaEnd(); ++i)
	nodo.agregarHijo((*i)->toXml());

  return nodo;
}

