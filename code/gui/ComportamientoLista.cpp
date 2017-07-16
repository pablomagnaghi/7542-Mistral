#include "ComportamientoLista.h"

#include "Comportamiento.h"
#include "ListaGui.h"
#include "FiguraLista.h"
#include "DialogFormatoCelda.h"

#include "./../Columna.h"

#include <sstream>
#include <iostream>
#include <gtkmm.h>

ComportamientoLista::ComportamientoLista( ListaGui* obj, FiguraLista* fig )
: obj(obj), fig(fig) {
  dragAndDrop = resize = false;

  // Creo el menu popup
  m_refActionGroup = Gtk::ActionGroup::create();

  //File|New sub menu:
  //These menu actions would normally already exist for a main menu, because a
  //context menu should not normally contain menu items that are only available
  //via a context menu.
  m_refActionGroup->add(Gtk::Action::create("ContextMenu", "Context Menu"));

  m_refActionGroup->add(Gtk::Action::create("formatoCelda", "Formato de Celda"),
          sigc::mem_fun(*this, &ComportamientoLista::formatearCelda));


  m_refActionGroup->add(Gtk::Action::create("agregarAdicional", "Agregar Adicional"),
          sigc::mem_fun(*this, &ComportamientoLista::agregarAdicional));

  m_refActionGroup->add(Gtk::Action::create("eliminarAdicional", "Eliminar Adicional"),
    sigc::mem_fun(*this, &ComportamientoLista::eliminarAdicional));

  m_refActionGroup->add(Gtk::Action::create("agregarColumna", "Agregar Columna"),
          sigc::mem_fun(*this, &ComportamientoLista::agregarColumna));

  m_refActionGroup->add(Gtk::Action::create("eliminarColumna", "Eliminar Columna"),
    sigc::mem_fun(*this, &ComportamientoLista::removeColumnaLista));


  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
        "<ui>"
        "  <popup name='PopupMenu'>"
        "    <menuitem action='agregarAdicional'/>"
        "    <menuitem action='eliminarAdicional'/>"
        "    <separator/>"
        "    <menuitem action='agregarColumna'/>"
        "    <menuitem action='eliminarColumna'/>"
        "  </popup>"
        "</ui>";

  try
  {
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  //Get the menu:
  m_pMenuPopup = dynamic_cast<Gtk::Menu*>(
          m_refUIManager->get_widget("/PopupMenu")); 
  if(!m_pMenuPopup)
    g_warning("menu not found");
}

bool ComportamientoLista::on_button_press_event (GdkEventButton* event ) {

  int numColumna = -1;
  tPosColumna posCol = COL_CENTRO;
  celda = NULL;
  tCelda = ENCABEZADO;

  fig->getTipoPocision( event->x, event->y, numColumna, 
			&colToResize, &celda, posCol, tCelda );

  if ( (colToResize)&&(tCelda==ADICIONAL)&&(celda) )
    std::cout << std::endl << colToResize->getNumColumna();

  dragAndDrop = resize  = false;

  if ( event->button == 1 ) {
    if ( Comportamiento::cercano( event->x, 
				  event->y, 
				  obj->getX() + obj->getAncho(), 
				 obj->getY() + obj->getAlto() ) ) {
      resize = true;
    }	
    else {
      dragAndDrop = true;
      deltaX = event->x - obj->getX();
      deltaY = event->y - obj->getY();
    }
  }
  else if ( event->button == 3 ) {
//     m_refActionGroup->get_action("formatoCelda")->set_sensitive( celda != NULL );

    m_refActionGroup->get_action("agregarAdicional")->set_sensitive(  numColumna!=-1  );
    m_refActionGroup->get_action("eliminarAdicional")->set_sensitive( tCelda==ADICIONAL  );

    m_refActionGroup->get_action("eliminarColumna")->set_sensitive( (numColumna!=-1)&&(obj->getLista()->getCantidadDeColumnas()>1)   );

    if(m_pMenuPopup)
      m_pMenuPopup->popup(event->button, event->time);
  }

  return true;
}

bool ComportamientoLista::on_button_release_event (GdkEventButton* event ) {
  dragAndDrop = resize  = false;
  return true;
}

bool ComportamientoLista::on_motion_notify_event (GdkEventMotion* event ) {
  if ( dragAndDrop ) {
    obj->setX( event->x - deltaX );
    obj->setY( event->y - deltaY );
  }
  if ( resize ) {
    obj->setAncho( event->x - obj->getX()  );
    obj->setAlto( event->y - obj->getY() );
  }
  return true;
}

void ComportamientoLista::removeColumnaLista() {
  this->obj->getLista()->eliminarColumna( this->colToResize );
}

// void ComportamientoLista::agregarAdicional();
void ComportamientoLista::eliminarAdicional() {
  if ( (colToResize)&&(tCelda==ADICIONAL)&&(celda) )
    this->colToResize->eliminarAdicional( celda );
}
  
void ComportamientoLista::formatearCelda() {
//   if ( celda && colToResize ) {
//     DialogFormatoCelda d ( celda->toString(), tCelda, celda->getId() );
//     int resultado = d.run();
// /*    d+=8;*/
//   }
}
  
void ComportamientoLista::agregarAdicional() {
  
 Texto* adicional = getTextoFromDialog();
    if ( adicional )
      colToResize->agregarTextosAdicionales( adicional );
}

void ComportamientoLista::agregarColumna() {

  Texto* textoCuerpo = getTextoFromDialog();
  if ( textoCuerpo ) {
    int numColumna = obj->getLista()->getCantidadDeColumnas();
    std::stringstream sstr;
    sstr << numColumna;
    std::string col("columna");
    col += sstr.str();

    obj->getLista()->agregarColumna( "Columna", textoCuerpo, 10 );
  }
}

Texto* ComportamientoLista::getTextoFromDialog() {

  Texto* miTexto = NULL;

  Gtk::HBox box;
  Gtk::Label label("Tipo de celda:");
  Gtk::ComboBoxText comboTipo;

  comboTipo.append_text("TEXTO FIJO");
  comboTipo.append_text("TEXTO VARIABLE");
  comboTipo.append_text("CALCULO");

  comboTipo.set_active( true );

  box.pack_start( label );
  box.pack_start( comboTipo );

  box.show();
  label.show();
  comboTipo.show();

  Gtk::Dialog dialogo;
  dialogo.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL );
  dialogo.add_button( Gtk::Stock::OPEN, Gtk::RESPONSE_OK );
  dialogo.get_vbox()->add( box );

  int resultado = dialogo.run();

  if ( resultado == Gtk::RESPONSE_OK ) {

    if ( comboTipo.get_active_row_number() == 0 ) {
      miTexto = new TextoFijo("texto fijo");
    }
    if ( comboTipo.get_active_row_number() == 1 ) {
      miTexto = new TextoVariable("./item/precio");
    }
    if ( comboTipo.get_active_row_number() == 2 ) {
      miTexto = new Calculo();
      ((Calculo*)miTexto)->obtenerElementos("15 + 5");
    }
  }

  return miTexto;
}
