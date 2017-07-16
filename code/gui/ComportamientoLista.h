#ifndef _COMPORTAMIENTO_LISTA_H_INCLUDED_
#define _COMPORTAMIENTO_LISTA_H_INCLUDED_

#include "Comportamiento.h"

#include "ListaGui.h"
#include "FiguraLista.h"
#include "./../Columna.h"
#include "./../Texto.h"

#include <gtkmm.h>

#include <iostream>

class ComportamientoLista : public Comportamiento {
private:
  ListaGui* obj;
  FiguraLista* fig;

  bool dragAndDrop;
  bool resize;

  Columna* colToResize;
  tPosColumna posCol;
  Texto* celda;
  tipoCelda tCelda;

  int deltaX;
  int deltaY;

  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

  Gtk::Menu* m_pMenuPopup;

  void removeColumnaLista();
  void agregarAdicional();
  void eliminarAdicional();
  void formatearCelda();
  void agregarColumna( );

  Texto* getTextoFromDialog();
public:
  ComportamientoLista( ListaGui*,FiguraLista* );
  bool on_button_press_event (GdkEventButton* event );
  bool on_button_release_event (GdkEventButton* event );
  bool on_motion_notify_event (GdkEventMotion* event );

void on_menu_file_popup_generic()
{
   std::cout << "A popup menu item was selected." << std::endl;
}

};

#endif
