#ifndef _WINDOW_NEW_CALCULO_H_INCLUDED_
#define _WINDOW_NEW_CALCULO_H_INCLUDED_

#include "./../Calculo.h"

#include <gtkmm.h>

class WindowNewCalculo : public Gtk::Dialog {
private:
    Gtk::HBox boxCuenta;
    Gtk::Label labelCuenta;
    Gtk::Entry entryCuenta;
  
public:
  WindowNewCalculo( Calculo& );
  ~WindowNewCalculo();

  std::string getOperacion();

};

#endif
