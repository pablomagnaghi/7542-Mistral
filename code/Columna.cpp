#include "Columna.h"
#include "ObjetoLista.h"

Columna::Columna( const std::string& nombreColumna, Texto* cuerpo,
		  int ancho, ObjetoLista& lista )
: miLista(lista) {
  this->encabezado  = new TextoFijo( nombreColumna );
  this->cuerpo = cuerpo;
  this->ancho = ancho;
  this->numColumna = 0; 

  cuerpo->setAlto( miLista.getAltoCelda() );
  cuerpo->setAncho( this->ancho );

  encabezado->setAlto( miLista.getAltoCelda() );
  encabezado->setAncho( this->ancho );
}

Columna::Columna( XmlNodo* nodo, ObjetoLista& lista )
: miLista(lista) {
  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);

  this->obtenerObjetosColumna(&nodoAux);
}

TextoFijo* Columna::getEncabezado() {
  this->encabezado->setPosX( miLista.getPosX()+miLista.getPosColumna(numColumna) );
  this->encabezado->setPosY( miLista.getPosY()+miLista.getAlto()-miLista.getAltoCelda() );
//   std::cout << std::endl << "Poniendo encabezado " << encabezado->toString() << " end pos Y=" << miLista.getPosY()+miLista.getAlto()-miLista.getAltoCelda();
  return encabezado;
}

Texto* Columna::getCuerpo(  int numItem  ) {
  this->cuerpo->setPosX( miLista.getPosX()+miLista.getPosColumna(numColumna) );
  cuerpo->setPosY( miLista.getPosY()+miLista.getAlto()-miLista.getAltoCelda()- ( (numItem+1)*miLista.getAltoCelda()) );
//   std::cout << std::endl << "Poniendo Cuerpo " << miLista.getAltoCelda() << " end pos Y=" << miLista.getPosY()+miLista.getAlto()-miLista.getAltoCelda()- ( (numItem+1)*miLista.getAltoCelda());
  return cuerpo;
}

void Columna::setCuerpo( Texto* cuerpo ) {
  cuerpo->setAlto( miLista.getAltoCelda() );
  cuerpo->setAncho( this->ancho );
  this->cuerpo = cuerpo;
}

void Columna::agregarTextosAdicionales( Texto* texto ) {
  texto->setAlto( miLista.getAltoCelda() );
  texto->setAncho( this->ancho );
  this->textosAdicionales.push_back( texto );
}

std::list<Texto*>::iterator Columna::listaBegin( int itemsEnLista ) {
  std::list<Texto*>::iterator it = textosAdicionales.begin();
  int numAdicional = 0;
  while ( it != textosAdicionales.end() ) {
    (*it)->setPosX( miLista.getPosX()+miLista.getPosColumna(numColumna) );

    int altoEncabezado = miLista.getAltoCelda();
    int altoCuerpo = (itemsEnLista) * miLista.getAltoCelda();
    int altoAdicionalesAnteriores = (numAdicional+1)*miLista.getAltoCelda();
    (*it)->setPosY( miLista.getPosY()+miLista.getAlto()-altoEncabezado-altoCuerpo-altoAdicionalesAnteriores );
    it++;
    numAdicional++;
   }
  return textosAdicionales.begin();
}

std::list<Texto*>::iterator Columna::listaEnd() {
  return textosAdicionales.end();
}


int Columna::getAncho() {
  return this->ancho;
}

void Columna::setAncho( int ancho ) {
  this->ancho = ancho;
  this->encabezado->setAncho( ancho );
  this->cuerpo->setAncho( ancho );

  std::list<Texto*>::iterator it = textosAdicionales.begin();

  while ( it != textosAdicionales.end() ) {
    (*it)->setAncho( ancho );
    it++;
   }
}
  
void Columna::setAltoCelda( int alto ) {
  
  this->encabezado->setAlto( alto );
  this->cuerpo->setAlto( alto );

  std::list<Texto*>::iterator it = textosAdicionales.begin();

  while ( it != textosAdicionales.end() ) {
    (*it)->setAlto( alto );
    it++;
   }
}

int Columna::getNumColumna() {
  return this->numColumna;
}

void Columna::setNumColumna( int num ) {
  this->numColumna = num;
}


int Columna::getporcentajeAnchoLista() {
  return this->porcentajeAnchoLista;
}

void Columna::setporcentajeAnchoLista( int porcentajeAnchoLista ) {
  this->porcentajeAnchoLista = porcentajeAnchoLista;
  this->setAncho ( miLista.getAncho()*porcentajeAnchoLista / 100 );
  //std::cout << std::endl << "Mi ancho es " << ancho;
}

Texto* Columna::getAdicional( int pos ) {

  Texto* adicional = NULL;

  std::list<Texto*>::iterator it = textosAdicionales.begin();
  int numAdicional = 0;
  while ( it != textosAdicionales.end() ) {
    if ( numAdicional == pos ) {
      adicional = (*it);
      it = textosAdicionales.end();
    }
    it++;
    numAdicional++;
  }

  if ( adicional )
    adicional->setAlto( miLista.getAltoCelda() );
  return adicional;
}
  
void Columna::eliminarAdicional( Texto* adicional ) {

  if ( adicional )
    std::cout << std::endl << "Intentando borrar adicional...";
  else
    std::cout << std::endl << "ERROR...";

  std::list<Texto*>::iterator it = textosAdicionales.begin();
  while ( (it != textosAdicionales.end()) && ( (*it)!=adicional ) ) {
    if ( (*it)!=adicional )
      it++;
  }

  if ( it != textosAdicionales.end() ) {
    textosAdicionales.erase( it );
  }
}


int Columna::getCantidadAdicionales() const {
  return textosAdicionales.size();
}

/* ******  Metodos para la persistencia  ********* */


Columna::~Columna() {
  delete this->encabezado;
  delete this->cuerpo;

  std::list<Texto*>::iterator it = textosAdicionales.begin();

   while ( it != this->listaEnd() ) {
     delete (*it);
     it++;
  }
  textosAdicionales.clear();

}

void Columna::agregarAtributos( XmlNodo* nodo) {
  XmlNodo nodoAncho( "ancho" );
  nodoAncho.setContenido( this->ancho );
  nodo->agregarHijo( nodoAncho );

  XmlNodo nodoPorcentajeAnchoLista( "porcentajeAnchoLista" );
  nodoPorcentajeAnchoLista.setContenido( this->porcentajeAnchoLista );
  nodo->agregarHijo( nodoPorcentajeAnchoLista );

  XmlNodo nodoNumColumna( "numColumna" );
  nodoNumColumna.setContenido( this->numColumna );
  nodo->agregarHijo( nodoNumColumna );

  XmlNodo nodoEncabezado( "encabezado" );
  nodoEncabezado.agregarHijo( this->encabezado->toXml() );
  nodo->agregarHijo( nodoEncabezado );

  XmlNodo nodoCuerpo( "cuerpo" );
  nodoCuerpo.agregarHijo( this->cuerpo->toXml() );
  nodo->agregarHijo( nodoCuerpo );
}

void Columna::obtenerAtributos ( XmlNodo* nodo ) {
  this->ancho = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->porcentajeAnchoLista = nodo->getContenidoInt();
  *nodo = nodo->getHermano();

  this->numColumna = nodo->getContenidoInt();
  *nodo = nodo->getHermano();
}

void Columna::obtenerObjetosColumna( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "encabezado" ) {
	  XmlNodo nodoAux = nodo->getHijo();
      this->obtenerTextoEncabezado( &nodoAux );
	}
	if ( nodo->getNombre() == "cuerpo" ) {
	  XmlNodo nodoAux = nodo->getHijo();
	  this->obtenerTextoCuerpo( &nodoAux );
	}
	if ( nodo->getNombre() == "textoAdicional" ) {
	  XmlNodo nodoAux = nodo->getHijo();
	  this->obtenerTextoAdicional( &nodoAux );
    }

    *nodo = nodo->getHermano();
  }
}

void Columna::obtenerTextoEncabezado( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "textoFijo" )
	  this->encabezado = new TextoFijo ( nodo );
	*nodo = nodo->getHermano();
  }
}

void Columna::obtenerTextoCuerpo( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "textoFijo" )
	  this->cuerpo = new TextoFijo ( nodo );

	if ( nodo->getNombre() == "textoVariable" )
	  this->cuerpo = new TextoVariable ( nodo );

	if ( nodo->getNombre() == "calculo" )
	  this->cuerpo = new Calculo ( nodo );

	*nodo = nodo->getHermano();
  }
}

void Columna::obtenerTextoAdicional( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "textoFijo" ) {
	  Texto* texto = new TextoFijo ( nodo );
	  this->agregarTextosAdicionales( texto );
	}

	if ( nodo->getNombre() == "textoVariable" ) {
	  Texto* texto = new TextoVariable ( nodo );
	  this->agregarTextosAdicionales( texto );
	}

	if ( nodo->getNombre() == "calculo" ) {
	  Texto* texto  = new Calculo ( nodo );
	  this->agregarTextosAdicionales( texto );
	}

	*nodo = nodo->getHermano();
  }
}


XmlNodo Columna::toXml() {
  XmlNodo nodo("columna");

  this->agregarAtributos( &nodo );

  XmlNodo nodoAdicionales( "textoAdicional" );

  std::list<Texto*>::iterator i;

  for(i = textosAdicionales.begin(); i != textosAdicionales.end(); ++i)
     nodoAdicionales.agregarHijo( (*i)->toXml() );

  nodo.agregarHijo( nodoAdicionales );

  return nodo;
}
