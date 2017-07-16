#include "FiguraCalculo.h"

#include "Figura.h"
#include "CalculoGui.h"

#include "Comportamiento.h"

#include "MyArea.h"
#include "WindowNewCalculo.h"

#include <gtkmm.h>

FiguraCalculo::FiguraCalculo( CalculoGui* txt, MyArea* area )
: FiguraRectangular( txt, area ), calculoGui(txt) {
}

FiguraRectangular* FiguraCalculo::clone( ObjetoGuiRectangular* obj ) {
  return new FiguraCalculo( (CalculoGui*)obj, this->getArea() );
}

ObjetoGui* FiguraCalculo::getObjetoGui() {
  return calculoGui;
}

void FiguraCalculo::draw() {
  FiguraRectangular::draw();


  MyArea* area = getArea();
  Glib::RefPtr<Gdk::Window> window = area->get_window();
  Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

  cr->rectangle( calculoGui->getX(), calculoGui->getY(), 
		 calculoGui->getAncho(), calculoGui->getAlto() );
  cr->clip();
int borde;
  ((ObjetoGui*)calculoGui)->getAttr( "borde", borde );
  cr->set_line_width(borde);
  Color c;
  std::string s("color");
  ((ObjetoGui*)calculoGui)->getAttr( s, c );
  double r,g,b;
  c.getCairoFormat( r,g,b );
  cr->set_source_rgb( r,g,b );

  cr->rectangle( calculoGui->getX(), calculoGui->getY(), 
		 calculoGui->getAncho(), calculoGui->getAlto() );

  cr->stroke();

  


   Cairo::TextExtents extents;
 
   cr->select_font_face (  "Sans",Cairo::FONT_SLANT_NORMAL,
 			  Cairo::FONT_WEIGHT_NORMAL);

   int size;
   calculoGui->getAttr("size",size);

  std::string txt( "Calculo:" );

   cr->set_font_size( size );
   cr->get_text_extents( txt.c_str(), extents);

  /* draw helping lines */

  //txt += calculoGui->getTitulo();
  
  cr->move_to ( calculoGui->getX()+borde, calculoGui->getY()+size+borde );
  cr->show_text ( txt.c_str() );
}


Gtk::Window* FiguraCalculo::getWindowParaConfigurar( int x , int y  ) {
  

    WindowNewCalculo dialogoCalculo( *this->calculoGui->getCalculo() );

    int res = Gtk::RESPONSE_OK;
    bool seguir = true;

    while ( (res == Gtk::RESPONSE_OK) && (seguir) ) {

      res = dialogoCalculo.run();
      calculoGui->getCalculo()->reiniciarConteo();
      seguir = !calculoGui->getCalculo()->obtenerElementos( dialogoCalculo.getOperacion() );

      if ( seguir ) {
	Gtk::MessageDialog dialog("Error");
	dialog.set_secondary_text( "Formato de operacion incorrecta.");
	dialog.run();
      }
    }

    return NULL;
}

