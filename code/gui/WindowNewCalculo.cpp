#include "WindowNewCalculo.h"

#include <gtkmm.h>
#include <iostream>

#include "./../OperandoConstante.h"
#include "./../OperandoVariable.h"

#include "./../Calculo.h"

#include <sstream>

WindowNewCalculo::WindowNewCalculo( Calculo& c ) 
: labelCuenta( "Cálculo" ) {

  entryCuenta.set_text( c.getCalculo() );

  boxCuenta.pack_start( labelCuenta );
  boxCuenta.pack_start( entryCuenta );

  this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

  this->get_vbox()->add( boxCuenta );
 

  entryCuenta.show();
  labelCuenta.show();
  boxCuenta.show();
}



std::string WindowNewCalculo::getOperacion() {
    return entryCuenta.get_text();
}

WindowNewCalculo::~WindowNewCalculo() {
}
