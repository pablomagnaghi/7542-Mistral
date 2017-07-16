#ifndef _DIALOG_TEST_POSTSCRIPT_H_INCLUDED_
#define _DIALOG_TEST_POSTSCRIPT_H_INCLUDED_
 
#include <gtkmm.h>


class DialogoTestPostScript : public Gtk::Dialog {
private:
  Gtk::HBox boxDocDeDatos;
  Gtk::Label labelDocDeDatos;
  Gtk::Entry entryDocDeDatos;

  Gtk::HBox boxArchivoDeSalida;
  Gtk::Label labelArchivoDeSalida;
  Gtk::Entry entryArchivoDeSalida;

public:
    DialogoTestPostScript( const std::string& tagDeDatos, 
			  const std::string& archivoDatosDef );

    std::string getArchivoDeDatos();
    std::string getArchivoDeSalida();
};

#endif