#include "FiguraLista.h"

#include "Figura.h"
#include "ListaGui.h"

#include "Comportamiento.h"
#include "ComportamientoLista.h"

#include <sstream>
#include "VisitorGui.h"
#include "MyArea.h"
#include "./../Texto.h"
#include "./../ObjetoLista.h"
#include "./../Columna.h"

#include "VisitorFigura.h"

#include <list>

FiguraLista::FiguraLista( ListaGui* l, MyArea* area )
: FiguraRectangular( l, area ), listaGui(l) {
}

FiguraRectangular* FiguraLista::clone( ObjetoGuiRectangular* obj ) {
  return new FiguraLista( (ListaGui*)obj, this->getArea() );
}

ObjetoGui* FiguraLista::getObjetoGui() {
  return this->listaGui;
}

void FiguraLista::dibujarTexto( int posX, int posY, Texto* txt, Cairo::RefPtr<Cairo::Context> cr  ) {
    // Dibujando encabezado
    Color c;
    std::string s("color");
    ((ObjetoGui*)listaGui)->getAttr( s, c );
    double r,g,b;
    c.getCairoFormat( r,g,b );
    cr->set_source_rgb( r,g,b );

    int borde;
    ((ObjetoGui*)listaGui)->getAttr( "borde", borde );
    cr->set_line_width(borde);

    cr->rectangle(    posX, posY, 
		      txt->getAncho(), listaGui->getLista()->getAltoCelda() );

  cr->stroke();
 
  int size = listaGui->getLista()->getSize();

  cr->select_font_face (  "Courirer",Cairo::FONT_SLANT_NORMAL,
 			  Cairo::FONT_WEIGHT_NORMAL);
  cr->set_font_size( size );
  
  cr->move_to ( posX + borde, posY + size + borde );
  cr->show_text ( txt->toString().c_str() );
    
}

void FiguraLista::dibujarColumna( Columna* col, int& posXActual, 
				  int& posYActual, Cairo::RefPtr<Cairo::Context> cr ) {


//    VisitorGui v ( getArea() );
//     col->getEncabezado()->accept( &v );
//     col->getCuerpo( 0 )->accept( &v );
//  
//    std::list<Texto*>::iterator itAdicionales = col->listaBegin( 1 );
//    while  ( itAdicionales != col->listaEnd()  ) {
//      (*itAdicionales)->accept( &v );    
//      itAdicionales++;
//    }

    ObjetoLista* lista = listaGui->getLista();

    
/*    int ancho = col->getAncho();*/
  
    dibujarTexto( posXActual, posYActual, col->getEncabezado(), cr );
    

    dibujarTexto( posXActual, posYActual+lista->getAltoCelda(),col->getCuerpo(0),cr );

    std::list<Texto*>::iterator it = col->listaBegin(0);



//     if ( it != col->listaEnd() ) { 
//       cr->move_to( posXActual, posYActual );
//       cr->line_to( posXActual, posYActual+( lista->getAltoCelda()* 3.5) );
// 
//       cr->move_to( posXActual+col->getAncho(), posYActual );
//       cr->line_to( posXActual+col->getAncho(), posYActual+( lista->getAltoCelda()* 3.5) );
// 
//       cr->save();
//       std::valarray< double > dashes(2);
//       dashes[0] = 2.0;
//       dashes[1] = 2.0;
//       cr->set_dash (dashes, 0.0);
//       cr->stroke();
//       cr->restore();
//     }

    int numAdicional = 0;
    while ( it != col->listaEnd() ) {
    dibujarTexto( posXActual,  posYActual+( lista->getAltoCelda()* (numAdicional+2) ),
		  col->getAdicional( numAdicional ), cr  );
      it++;
      numAdicional++;
    }

    posXActual += col->getAncho();

}


void FiguraLista::draw() {
  FiguraRectangular::draw();

   MyArea* area = getArea();
   Glib::RefPtr<Gdk::Window> window = area->get_window();
   Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
 
 
     ObjetoLista* lista = listaGui->getLista();
 
     std::list<Columna*>::iterator it = lista->columnasBegin();
  
    int posXActual = listaGui->getX();
    int posYActual = listaGui->getY();

    while ( it != lista->columnasEnd() ) {
      Columna* col = (*it);
      dibujarColumna( col, posXActual, posYActual, cr );
      it++;
    }

    cr->set_line_width( 1.0 );
    cr->set_source_rgb( 0.5,0.5,0.5 );
    cr->rectangle(  listaGui->getX(), listaGui->getY(), 
		    lista->getAncho(), lista->getAlto() );

    std::valarray< double > dashes(2);
    dashes[0] = 2.0;
    dashes[1] = 2.0;
    
    cr->set_dash (dashes, 0.0);
    cr->stroke();
}


Gtk::Window* FiguraLista::getWindowParaConfigurar( int x , int y  ) {

  ObjetoLista* lista = listaGui->getLista();
 
  std::list<Columna*>::iterator it = lista->columnasBegin();
  
  int posXIzq = listaGui->getX();
  int posXDer = posXIzq;
  bool pertenece = false;

  while ( (it != lista->columnasEnd()) && (!pertenece) ) {
    posXDer += (*it)->getAncho();
    pertenece = ( (posXIzq<x)&&(posXDer>x) );
    posXIzq = posXDer;
    if ( !pertenece ) 
      it++;
  }



  if ( (pertenece)&&(lista->getAltoCelda()>0) &&(it != lista->columnasEnd() ) ) {
    
    std::cout.flush();
    VisitorFigura vFigura( this->getArea() );

     float n = ( ( y - listaGui->getY() ) / lista->getAltoCelda() );
     int numFila = (int)n;
 
    std::cout << std::endl << "Pidienddo fila:" << numFila << " de " <<  (*it)->getCantidadAdicionales();

     if ( numFila == 0 )
       (*it)->getEncabezado()->accept( &vFigura );
     else if ( numFila == 1 )
       (*it)->getCuerpo(0)->accept( &vFigura );
     else if ( (numFila-2) < (*it)->getCantidadAdicionales() ) {
	Texto* adicional = (*it)->getAdicional( numFila - 2 );
	if ( adicional )
	  adicional->accept( &vFigura );
      }

     Figura* f = vFigura.getFiguraCreada();

     if ( f )  {
       f->getWindowParaConfigurar( x, y );
/*     f->draw();*/
     }

  }

  return NULL;
}

void FiguraLista::getTipoPocision( int x, int y, int& numColumna, Columna** col, 
		      Texto** txt, tPosColumna& posCol, tipoCelda& tipo ) {

  numColumna = 0;

  ObjetoLista* lista = listaGui->getLista();
 
  std::list<Columna*>::iterator it = lista->columnasBegin();
  
  int posXIzq = listaGui->getX();
  int posXDer = posXIzq;
  bool pertenece = false;

  while ( (it != lista->columnasEnd()) && (!pertenece) ) {
    posXDer += (*it)->getAncho();
    pertenece = ( (posXIzq<x)&&(posXDer>x) );
    if ( !pertenece ) {
      it++;
      numColumna++;
      posXIzq = posXDer;
    }
  }


  if ( (pertenece)&&(lista->getAltoCelda()>0) &&(it != lista->columnasEnd() ) ) {
    (*col) = (*it);
    posCol = COL_CENTRO;

    if ( (x-posXIzq < 5)&&(numColumna>0) )
      posCol = COL_IZQUIERDA;
    else if ( (posXDer - x < 5)&&(numColumna<lista->getCantidadDeColumnas() ))
      posCol = COL_DERECHA;

    VisitorFigura vFigura( this->getArea() );

    float n = ( ( y - listaGui->getY() ) / lista->getAltoCelda() );
    int numFila = (int)n;
 
    if ( numFila == 0 ) {
      (*txt) = (*it)->getEncabezado();
      tipo = ENCABEZADO;
    }
     else if ( numFila == 1 ) {
      (*txt) = (*it)->getCuerpo( 0 );
      tipo = CUERPO;
    }
    else if ( (numFila-2) < (*it)->getCantidadAdicionales() ) {
      (*txt) = (*it)->getAdicional( numFila - 2 );
      tipo = ADICIONAL;
    }
  }
  else {
    (*col) = NULL;
  }

}

Comportamiento* FiguraLista::getComportamiento() {
  return new ComportamientoLista( this->listaGui, this );
}

