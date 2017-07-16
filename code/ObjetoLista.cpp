#include "ObjetoLista.h"

#include "Visitor.h"
#include "ObjetoGrafico.h"
#include "XmlNodo.h"
#include "TextoFijo.h"

#include <iostream>

ObjetoLista::ObjetoLista( int posX, int posY, int cR, int cV, int cA, int borde, int ancho,
		int alto, int size, const std::string& tipoFuente, const std::string& xpath )
: Texto ( posX, posY, cR, cV, cA, borde, ancho, alto, size, tipoFuente ) {
  this->xpath = xpath;
}

ObjetoLista::ObjetoLista( int ancho, int alto, const std::string& xpath )
: Texto ( POSX, POSY, 0, 0, 0, BORDE, ancho, alto, SIZE, LETRA ) {
  this->xpath = xpath;
}

ObjetoLista::ObjetoLista( const std::string& xpath )
: Texto ( POSX, POSY, 0, 0, 0, BORDE, ANCHO, ALTO, SIZE, LETRA ) {
  this->xpath = xpath;
}


ObjetoGraficoRectangular* ObjetoLista::clone() {
   TextoVariable* txtCol1 = new TextoVariable("./precio");
   TextoVariable* txtCol2 = new TextoVariable("./cantidad");
   Calculo* txtCol3 = new Calculo();
   txtCol3->obtenerElementos("\"./precio\" * \"./cantidad\"");

   ObjetoLista* lista = new ObjetoLista("./item");
   lista->agregarColumna( "Precio",txtCol1,25 );
   lista->agregarColumna( "Cantidad",txtCol2,25 );
   lista->agregarColumna( "Producto",txtCol3,50 );

   TextoFijo* txtAdA1 = new TextoFijo("iva");
   TextoVariable* txtAdA2 = new TextoVariable("./iva");

   TextoFijo* txtAdB1 = new TextoFijo("total");
   TextoVariable* txtAdB2 = new TextoVariable("./total");

   lista->agregarAdicional(1,txtAdA1);
   lista->agregarAdicional(1,txtAdB1);
   lista->agregarAdicional(2,txtAdA2);
   lista->agregarAdicional(2,txtAdB2);

   return lista;
}

void ObjetoLista::agregarColumna( Columna* columna ) {
  columna->setNumColumna( misColumnas.size() );
  this->misColumnas.push_back( columna );

  Columna* ultimacolumna = NULL;
  std::list<Columna*>::iterator it = this->columnasBegin();
  int cantidad = misColumnas.size();
  int sumatoria = 0;
  while ( it != this->columnasEnd() ) {
    ultimacolumna = (*it);
    (*it)->setporcentajeAnchoLista( 100 / cantidad);
    sumatoria +=  100 / cantidad;
    it++;
  }

  if ( ultimacolumna )
    ultimacolumna->setporcentajeAnchoLista( 100 / cantidad + 100-sumatoria );

}

void ObjetoLista::agregarColumna( std::string nombre,Texto* textoCuerpo,
				  int porcentajeAncho ) {
  Columna* f = new Columna( nombre, textoCuerpo, 0, *this );
  this->agregarColumna( f );
}

int ObjetoLista::getPosColumna( int numColumna ) {
  int pos = 0;
  if ( numColumna < (int)misColumnas.size() ) {
  
    int n = 0;
    std::list<Columna*>::iterator it = this->columnasBegin();
 
    while ( (n<numColumna) && (it != this->columnasEnd()) ) {
      pos += (*it)->getAncho();
      it++;
      n++;

    }
  }

  return pos;
}

int ObjetoLista::getAltoCelda() {
  return ( this->getSize() + (this->getBorde()*8) );
}

bool ObjetoLista::agregarAdicional( int numColumna, Texto* adicional ) {
  if ( numColumna < (int)misColumnas.size() ) {
    std::list<Columna*>::iterator cols = misColumnas.begin();
    int actual = 0;
    while ( actual < numColumna ) {
      actual++;
      cols++;
    }
    Columna* col = (*cols);
    col->agregarTextosAdicionales( adicional );
  }
  return ( numColumna < (int)misColumnas.size() );
}
  
Columna* ObjetoLista::getColumna( unsigned int pos ) {
  Columna* col = NULL;
  if ( (pos>0) && (pos<misColumnas.size()) ) {
 
    std::list<Columna*>::iterator cols = misColumnas.begin();
    unsigned int actual = 0;
    while ( actual < pos ) {
      actual++;
      cols++;
    }
    col = (*cols);
  }
  return col;
}

void ObjetoLista::resizeColumna( Columna* col, int deltaX, bool ladoIzquierdo ) {
  
 

  int deltaPorcentaje = deltaX*100 / this->getAncho();
  col->setporcentajeAnchoLista( col->getporcentajeAnchoLista()+deltaPorcentaje );

  Columna* vecino = NULL;
  if ( ladoIzquierdo )
    vecino = getColumna( col->getNumColumna()-1 );
  else
    vecino = getColumna( col->getNumColumna()+1 );

  if ( vecino )
  vecino->setporcentajeAnchoLista( col->getporcentajeAnchoLista()-deltaPorcentaje );
   std::cout << std::endl << "resize deltaPor:" <<  deltaPorcentaje;
}

int ObjetoLista::getCantidadDeColumnas() const {
  return this->misColumnas.size();
}

void ObjetoLista::eliminarColumna( Columna* col ) {
  if ( col )
    std::cout << std::endl << col->getNumColumna();

  std::list<Columna*>::iterator it = this->columnasBegin();
 
  while ( (it != this->columnasEnd()) && ( (*it) != col ) ) {
    if ( (*it) != col ) {
      it++;
    }
  }

  if ( (*it) == (col) ) {
    int sumatoria = 0;

    int porcentajeEliminado = col->getporcentajeAnchoLista();
    misColumnas.erase( it );
    delete col;
    
    it = this->columnasBegin();
    while ( it != this->columnasEnd() ) {
      int pc = (*it)->getporcentajeAnchoLista();
      sumatoria += (pc*100)/(100-porcentajeEliminado);
      (*it)->setporcentajeAnchoLista( (pc*100)/(100-porcentajeEliminado)  );
      it++;
    }

    it = this->columnasBegin();
    if ( it != columnasEnd() ) {
      int porcentaje = (*it)->getporcentajeAnchoLista();
      (*it)->setporcentajeAnchoLista( 100 - sumatoria + porcentaje );
    }
  }
}

void ObjetoLista::setAncho( int ancho ) {

  std::list<Columna*>::iterator it = this->columnasBegin();
 
   while ( it != this->columnasEnd() ) {
     int valor =(int) ancho * (*it)->getporcentajeAnchoLista() / 100;
      (*it)->setAncho( valor );
     it++;
   }

  ObjetoGraficoRectangular::setAncho( ancho );
}

void ObjetoLista::setSize( int size ) {
  std::list<Columna*>::iterator it = this->columnasBegin();
 
   while ( it != this->columnasEnd() ) {
     (*it)->setAltoCelda( this->getSize() + (this->getBorde()*8)  );
     it++;
   }

  Texto::setSize( size );
}


// Persistencia

ObjetoLista::ObjetoLista( XmlNodo* nodo ) {
  this->obtenerPropiedades(nodo);

  XmlNodo nodoAux = nodo->getHijo();

  this->obtenerAtributos(&nodoAux);

  this->obtenerObjetosLista(&nodoAux);
}

ObjetoLista::~ObjetoLista()  {
   std::list<Columna*>::iterator it = this->columnasBegin();

   while ( it != this->columnasEnd() ) {
     delete (*it);
     it++;
   }

   misColumnas.clear();
}

void ObjetoLista::obtenerObjetosLista( XmlNodo* nodo) {
  while (nodo->esValido()) {
	if ( nodo->getNombre() == "columna" ) {
	  Columna* columna = new Columna( nodo, *this );
	  this->agregarColumna( columna );
	}

	*nodo = nodo->getHermano();
  }
}

void ObjetoLista::agregarAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::agregarAtributos(nodo);

  XmlNodo nodoXpath("xpath");
  nodoXpath.setContenido(this->xpath);
  nodo->agregarHijo(nodoXpath);
}

void ObjetoLista::obtenerAtributos ( XmlNodo* nodo ) {
  ObjetoGraficoRectangular::obtenerAtributos(nodo);

  this->xpath = nodo->getContenido();
  *nodo = nodo->getHermano();
}

void ObjetoLista::accept( Visitor* v ) {
  v->visit( *this );
}

void ObjetoLista::setXpath(const std::string& xpath) {
  this->xpath = xpath;
}

std::string ObjetoLista::getXpath() {
  return this->xpath;
}

std::list<Columna*>::iterator ObjetoLista::columnasBegin() {
  return misColumnas.begin();

}

std::list<Columna*>::iterator ObjetoLista::columnasEnd() {
  return misColumnas.end();
}


XmlNodo ObjetoLista::toXml() {
  XmlNodo nodo("objetoLista");

  this->agregarPropiedades( &nodo );
  this->agregarAtributos( &nodo );

  std::list<Columna*>::iterator i;

  for(i = this->columnasBegin(); i != this->columnasEnd(); ++i)
	nodo.agregarHijo( (*i)->toXml() );

  return nodo;
}
