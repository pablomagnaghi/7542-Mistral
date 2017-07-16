#include "FiguraTextoFijo.h"

#include "Figura.h"
#include "TextoFijoGui.h"

#include "Comportamiento.h"

#include "MyArea.h"
#include "./Color.h"

FiguraTextoFijo::FiguraTextoFijo( TextoFijoGui* txt, MyArea* area )
: FiguraRectangular( txt, area ), txtGui(txt) {
}

FiguraRectangular* FiguraTextoFijo::clone( ObjetoGuiRectangular* obj ) {
  return new FiguraTextoFijo( (TextoFijoGui*)obj, this->getArea() );
}

ObjetoGui* FiguraTextoFijo::getObjetoGui() {
  return this->txtGui;
}	

void FiguraTextoFijo::draw() {
  FiguraRectangular::draw();
  MyArea* area = getArea();
  Glib::RefPtr<Gdk::Window> window = area->get_window();
  Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

  cr->rectangle( txtGui->getX(), txtGui->getY(), txtGui->getAncho(), txtGui->getAlto() );
  cr->clip();

  int borde;
  ((ObjetoGui*)txtGui)->getAttr( "borde", borde );
  cr->set_line_width(borde);

  Color c;
  std::string s("color");
  ((ObjetoGui*)txtGui)->getAttr( s, c );
  double r,g,b;
  c.getCairoFormat( r,g,b );
  cr->set_source_rgb( r,g,b );

  cr->rectangle( txtGui->getX(), txtGui->getY(), txtGui->getAncho(), txtGui->getAlto() );
  cr->stroke();


   Cairo::TextExtents extents;
 
   cr->select_font_face (  "Sans",Cairo::FONT_SLANT_NORMAL,
 			  Cairo::FONT_WEIGHT_NORMAL);

    int size;
    txtGui->getAttr("size", size);
   cr->set_font_size( size );
   cr->get_text_extents( txtGui->getTexto().c_str(), extents);

  /* draw helping lines */

  cr->move_to ( txtGui->getX() + borde, txtGui->getY() + size + borde );
  cr->show_text ( txtGui->getTexto().c_str() );
}


Gtk::Window* FiguraTextoFijo::getWindowParaConfigurar( int x , int y  ) {

  Gtk::HBox boxXpath;
  Gtk::Entry entryXpath;
  Gtk::Label labelXpath("texto");

  boxXpath.pack_start( labelXpath );
  boxXpath.pack_start( entryXpath );

  labelXpath.show();
  entryXpath.show();
  boxXpath.show();

  entryXpath.set_text( txtGui->getTexto() );
  Gtk::Dialog dialog;

  dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
  dialog.add_button( Gtk::Stock::OPEN, Gtk::RESPONSE_OK );

  dialog.get_vbox()->pack_start( boxXpath );

  int resultado = dialog.run();

  if ( resultado ==  Gtk::RESPONSE_OK )
    txtGui->setTexto( entryXpath.get_text() );

  return NULL;
}
