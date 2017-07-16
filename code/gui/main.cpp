#include <gtkmm-2.4/gtkmm.h>
#include <iostream>
#include <gtkmm.h>
#include "MyArea.h"
#include <sstream>
#include "./../DocTemplate.h"
#include "./../Template.h"
#include "./../Fecha.h"

#include "DialogNewTemplate.h"

#include "ComportamientoNewLinea.h"
#include "ComportamientoNewObjRectangular.h"
#include "ComportamientoSeleccion.h"

#include "TextoFijoGui.h"
#include "FiguraTextoFijo.h"


#include "LineaGui.h"
#include "FiguraLinea.h"

#include "TextoVariableGui.h"
#include "FiguraTextoVariable.h"

#include "CalculoGui.h"
#include "./../OperandoVariable.h"
#include "./../OperandoConstante.h"

#include "FiguraCalculo.h"

#include "ListaGui.h"
#include "FiguraLista.h"

#include "ObjetoMap.h"
#include "TipoAtributo.h"
#include "TipoBool.h"
#include "TipoString.h"
#include "TipoInt.h"
#include "TipoColor.h"
#include "Color.h"

#include "ComboVersiones.h"
#include "TablaDePropiedades.h"

#include "./../Calculo.h"
#include "./../ObjetoLista.h"
#include "./../Columna.h"

#include "./../TextoFijo.h"
#include "./../TextoVariable.h"

#include "./../VisitorPostScript.h"
#include "./../Xml.h"
#include "./../XmlNodo.h"
#include "./../XmlNodeSet.h"

#include "WindowNewDoc.h"
#include "WindowNewVersion.h"
#include "DialogoTestPostScript.h"
#include "DialogoInsertarImagen.h"

#include "./../ObjetoGraficoRectangular.h"

#include "ContextoEditor.h"


void newTemplate( ContextoEditor* ctxEditor1 );
void newVersion( ContextoEditor* ctxEditor1 );
void saveAsTemplate( ContextoEditor* ctxEditor1 );
void saveTemplate( ContextoEditor* ctxEditor1 );
void openTemplate( ContextoEditor* ctxEditor1 );
void propDocTemplate( ContextoEditor* );
void propVersion( ContextoEditor* );

void newVersion( ContextoEditor* ctxEditor1 ) {
  if ( ctxEditor1->tieneDocumento() ) {
      WindowNewVersion dialog;
      int res = dialog.run();
      if ( res == Gtk::RESPONSE_OK ) {
	Fecha f;
	Template* nuevoTemplate = new Template( "a4",
						dialog.getFechaDesde(), 
						dialog.getFechaHasta(), 
						dialog.getDescripcion() );
	ctxEditor1->newVersion( nuevoTemplate );
      }
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una plantilla para agregar versiones.");
    dialog.run();
  }
}

void newTemplate( ContextoEditor* ctxEditor1 ) {
  if ( ctxEditor1->tieneDocumento() ) {
    saveTemplate(ctxEditor1);
  }

  WindowNewDoc newDocDialog;
  int result = newDocDialog.run();

  if ( result == Gtk::RESPONSE_OK ) {
    DocTemplate* docNuevo = new DocTemplate( newDocDialog.getNombre(), 
					    newDocDialog.getDescripcion(),
					    newDocDialog.getTag() );
    ctxEditor1->newDocumento( docNuevo );
    newVersion(ctxEditor1);
  }
}

void saveTemplate( ContextoEditor* ctxEditor1 ) {
  if ( ctxEditor1->tieneDocumento() ) {
    if ( ctxEditor1->tieneArchivo() )
      ctxEditor1->save();
    else		
      saveAsTemplate(ctxEditor1);
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una plantilla abierta para guardar.");
    dialog.run();
  }
}

void saveAsTemplate( ContextoEditor* ctxEditor1 ) {

  // Si hay un docmuento abro un dialogo para guardarlo.
  if ( ctxEditor1->tieneDocumento() ) {
    Gtk::FileChooserDialog dialog("Guardar plantilla...",
				  Gtk::FILE_CHOOSER_ACTION_SAVE );

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

    int result = dialog.run();

    if ( result == Gtk::RESPONSE_OK ) {
      ctxEditor1->save();
      std::string fileName = dialog.get_filename();
      fileName += ".xml";
      ctxEditor1->saveAs( fileName );
    }
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una plantilla abierta para guardar.");
    dialog.run();
  }
}

void openTemplate( ContextoEditor* ctxEditor1 ) {
     Gtk::FileChooserDialog dialog("Abrir plantilla...",
           Gtk::FILE_CHOOSER_ACTION_OPEN );
 
     //Add response buttons the the dialog:
     dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
     dialog.add_button("Select", Gtk::RESPONSE_OK);
 
     int result = dialog.run();
 
     if ( result == Gtk::RESPONSE_OK ) {
       std::string fileName = dialog.get_filename();

      if ( ! ctxEditor1->openDocumento( fileName ) ) {
	  Gtk::MessageDialog dialogError("Error");
	  dialogError.set_secondary_text( "Error al abrir plantilla desde archivo." );
	  dialogError.run();  
      }
    }
}

void salirDeAplicacion( ContextoEditor* ctxEditor1 ) {
  Gtk::Main::quit();
}

void propDocTemplate( ContextoEditor* ctxEditor1 ) {
  if ( ctxEditor1->tieneDocumento() ) {
    DocTemplate* docTemplate = ctxEditor1->getDocumento();
    WindowNewDoc newDocDialog( *docTemplate );
    int result = newDocDialog.run();

    if ( result == Gtk::RESPONSE_OK ) {
      docTemplate->setNombre( newDocDialog.getNombre() );
      docTemplate->setDescripcion( newDocDialog.getDescripcion());
      docTemplate->setXpathNodoDatos( newDocDialog.getTag() );
    }
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una plantilla abierta.");
    dialog.run();
  }
}

void propVersion( ContextoEditor* ctxEditor1 ) {
  if ( ctxEditor1->tieneVersionDeTrabajo() ) {
    WindowNewVersion newVersionDialog( *ctxEditor1->getVersionDeTrabajo() );
    int result = newVersionDialog.run();

    if ( result == Gtk::RESPONSE_OK ) {
      ctxEditor1->getVersionDeTrabajo()->setDescripcion( newVersionDialog.getDescripcion());

       ctxEditor1->getVersionDeTrabajo()->setValidoDesde( newVersionDialog.getFechaDesde() );

       ctxEditor1->getVersionDeTrabajo()->setValidoHasta( newVersionDialog.getFechaHasta() );
    }
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una version de plantilla seleccionada.");
    dialog.run();
  }
}

void testPS( ContextoEditor* ctxEditor1 ) {
  static std::string archivoDatosDefault = "./datos.xml";

  if ( ctxEditor1->getVersionDeTrabajo() ) {
    DocTemplate* doc = ctxEditor1->getDocumento();
    DialogoTestPostScript dialogo( doc->getXpathNodoDatos(), archivoDatosDefault );
    int resultado = dialogo.run();
    if ( resultado == Gtk::RESPONSE_OK ) {

      try {
	std::string patharchivoDeSalida = dialogo.getArchivoDeSalida();
	std::string patharchivoDeDatos = dialogo.getArchivoDeDatos();
	archivoDatosDefault = patharchivoDeDatos;

	Xml archivoDeDatos( patharchivoDeDatos );
	
	std::ofstream filePostScript( patharchivoDeSalida.c_str() );

	archivoDeDatos.crearContextoXpath();

	// Tomo la raíz, evaluo la expresion buscando nodos para el template
	XmlNodo* raiz = archivoDeDatos.getNodoRaiz();
	archivoDeDatos.setCurrentNode( *raiz );
	std::string tagDeDatos = ctxEditor1->getDocumento()->getXpathNodoDatos();
	XmlNodeSet nodosDeDatos = archivoDeDatos.evaluarExpresion( tagDeDatos );

	if ( nodosDeDatos.size() > 0 ) {
	  XmlNodo nodoActual = nodosDeDatos.getNodo(0);
	  archivoDeDatos.setCurrentNode( nodoActual );
	  VisitorPostScript v( &archivoDeDatos, filePostScript, std::cerr );
	  ctxEditor1->getVersionDeTrabajo()->getHoja()->accept( &v );
	}
      }
      catch ( Exception* ex ) {
	std::cerr << std::endl << ex->getMsjError();
	delete ex;

	Gtk::MessageDialog dialog("Error");
	dialog.set_secondary_text(
          "No se pudo correr el test.");
	dialog.run();

      }
    }
  }
  else {
    Gtk::MessageDialog dialog("Error");
    dialog.set_secondary_text(
          "No hay una version de plantilla seleccionada.");
    dialog.run();
  }
}

void insertarImagen( MyArea* area ) {
  DialogoInsertarImagen dialogo( area->getImagen(), area->tieneImagenDeFondo() );
  int resultado = dialogo.run();

  if ( resultado == Gtk::RESPONSE_OK ) {
    area->cargarImagen( dialogo.getArchivoDeImagen() );
  }
  else if ( resultado == 7 ) {
    area->sacarImagen();
  }
}

void crearMenu( Gtk::VBox& boxMenu, Gtk::VBox& m_Box, 
		Gtk::Window& ventanaPrincipal, ContextoEditor& ctxEditor,
		MyArea* area ) {

  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

  m_refActionGroup = Gtk::ActionGroup::create();

  //Menu File
  Glib::RefPtr<Gtk::Action> actionArchivo = Gtk::Action::create("archivo", "_Archivo");
  m_refActionGroup->add( actionArchivo );

  m_refActionGroup->add(  Gtk::Action::create("nuevo",  Gtk::Stock::NEW, 
					      "_Nueva plantilla","Nuevo"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&newTemplate), &ctxEditor ) );


  Glib::RefPtr<Gtk::Action> actionNewV = Gtk::Action::create( "nuevo_v",
							      Gtk::Stock::ADD,
							      "_Nueva versión",
							      "Nuevo");
  m_refActionGroup->add(  actionNewV, sigc::bind<ContextoEditor*>
  ( sigc::ptr_fun(&newVersion), &ctxEditor ) );


  Glib::RefPtr<Gtk::Action> actionAbrir = Gtk::Action::create( "abrir",   										     Gtk::Stock::OPEN,
						               "_Abrir...", 			"Abrir");
  m_refActionGroup->add( actionAbrir,
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&openTemplate), &ctxEditor ) );


  m_refActionGroup->add( Gtk::Action::create( "guardar", Gtk::Stock::SAVE, 								    "_Guardar","Guardar"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&saveTemplate), &ctxEditor ) );


  m_refActionGroup->add( Gtk::Action::create( "guardar_como",  Gtk::Stock::SAVE_AS,              					    "Guardar _Como...", "Guardar Como"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&saveAsTemplate), &ctxEditor ) );


  m_refActionGroup->add( Gtk::Action::create( "salir",Gtk::Stock::QUIT, 								    "_Salir","Salir"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&salirDeAplicacion), &ctxEditor ) );


  m_refActionGroup->add(  Gtk::Action::create("documento", "Documento","Documento") );

  // Propiedades del documento.
  m_refActionGroup->add( Gtk::Action::create( "prop_plantilla",
					      "Propiedades de plantilla",
					      "Propiedades de plantilla"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&propDocTemplate), &ctxEditor ) );


  m_refActionGroup->add( Gtk::Action::create("prop_version",
					     "Propiedades de version",
					     "Propiedades de version"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&propVersion), &ctxEditor ) );

  // Test postscript
  m_refActionGroup->add( Gtk::Action::create( "test_ps", Gtk::Stock::EXECUTE
					      ,"Test PostScript","Test PostScript"),
  sigc::bind<ContextoEditor*>( sigc::ptr_fun(&testPS), &ctxEditor ) );

  // Imagen de fondo
  m_refActionGroup->add( Gtk::Action::create( "imagen_de_fondo",
					      "Imágen de fondo","Imágen de fondo"),
  sigc::bind<MyArea*>( sigc::ptr_fun(&insertarImagen), area ) );

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  ventanaPrincipal.add_accel_group(m_refUIManager->get_accel_group());

  Glib::ustring ui_info = "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='archivo'>"
    "        <menuitem action='nuevo'/>"
    "        <menuitem action='nuevo_v'/>"
    "        <separator/>"
    "        <menuitem action='abrir'/>"
    "        <separator/>"
    "        <menuitem action='guardar'/>"
    "        <menuitem action='guardar_como'/>"
    "        <separator/>"
    "        <menuitem action='salir'/>"
    "    </menu>"
    "    <menu action='documento'>"
    "        <menuitem action='prop_plantilla'/>"
    "        <menuitem action='prop_version'/>"
    "        <separator/>"
    "        <menuitem action='test_ps'/>"
    "        <menuitem action='imagen_de_fondo'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar  name='ToolBar'>"
    "    <toolitem action='nuevo'/>"
    "    <toolitem action='nuevo_v'/>"
    "    <separator/>"
    "    <toolitem action='abrir'/>"
    "    <separator/>"
    "    <toolitem action='guardar'/>"
    "    <toolitem action='guardar_como'/>"
    "    <separator/>"
    "    <toolitem action='test_ps'/>"
    "  </toolbar>"
    "</ui>";


  m_refUIManager->add_ui_from_string(ui_info);
  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
  boxMenu.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
  m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);


  boxMenu.add(*pMenubar);
}


void inicializarHerramientas( MyArea* area, Glib::RefPtr<Gtk::Builder> builder,
			      TablaDePropiedades& tabla ) {

  Gtk::Button * botonPuntero = 0;
  builder->get_widget("botonPuntero", botonPuntero);
  botonPuntero->signal_clicked().connect(sigc::bind<bool,Figura*>( sigc::mem_fun( area,&MyArea::setComportamientoSeleccion), false, NULL ) );

  static ComportamientoNewLinea cNewLinea( area, tabla  );

  Gtk::Button * botonLinea = 0;
  builder->get_widget("botonLinea", botonLinea);
  botonLinea->signal_clicked().connect(sigc::bind<Comportamiento*>( sigc::mem_fun( area,&MyArea::setComportamiento), &cNewLinea ) );
 
   static TextoFijo txt("Texto Fijo");
   static TextoFijoGui oR( txt );
   oR.setTexto( "un texto fijo" ); 
   static FiguraTextoFijo fR( &oR, area );
   static ComportamientoNewObjetoRectangular cNewR( area, &fR, &oR, &txt, tabla  );

   Gtk::Button * botonTextoFijo = 0;
   builder->get_widget("botonTextoFijo", botonTextoFijo);
   botonTextoFijo->signal_clicked().connect(sigc::bind<Comportamiento*>( sigc::mem_fun( area,&MyArea::setComportamiento), &cNewR ) );


   static TextoVariable txtVariable( "./titulo" );
   static TextoVariableGui txtVariableGui( txtVariable );
   txtVariableGui.setTextoXpath(  "./titulo"  ); 
   static FiguraTextoVariable fTxtVariable( &txtVariableGui, area );
   static ComportamientoNewObjetoRectangular cNewT( area, &fTxtVariable, &txtVariableGui, &txtVariable, tabla  );

   Gtk::Button * botonTextoVariable = 0;
   builder->get_widget("botonTextoVariable", botonTextoVariable);
   botonTextoVariable->signal_clicked().connect(sigc::bind<Comportamiento*>( sigc::mem_fun( area,&MyArea::setComportamiento), &cNewT ) );

   static Calculo calculo;
   static CalculoGui calculoGui( calculo );
   static FiguraCalculo fcalculo( &calculoGui, area );
   static ComportamientoNewObjetoRectangular cNewC( area, &fcalculo, &calculoGui, &calculo, tabla  );

   Gtk::Button * botonCalculo = 0;
   builder->get_widget("botonCalculo", botonCalculo);
   botonCalculo->signal_clicked().connect(sigc::bind<Comportamiento*>( sigc::mem_fun( area,&MyArea::setComportamiento), &cNewC ) );
    
   static TextoVariable* txtCol1 = new TextoVariable("./Precio");
   static TextoVariable* txtCol2 = new TextoVariable("./cantidad");
   static TextoVariable* txtCol3 = new TextoVariable("./cantidad");

   static ObjetoLista* lista = new ObjetoLista("./descripcion");
   lista->agregarColumna( "Precio",txtCol1,25 );
   lista->agregarColumna( "Cantidad",txtCol2,25 );
   lista->agregarColumna( "Producto",txtCol3,50 );

   static TextoFijo* txtAdA1 = new TextoFijo("iva");
   static TextoFijo* txtAdA2 = new TextoFijo("titulo");

   static TextoFijo* txtAdB1 = new TextoFijo("iva");
   static TextoVariable* txtAdB2 = new TextoVariable("./titulo");

   lista->agregarAdicional(1,txtAdA1);
   lista->agregarAdicional(1,txtAdA2);
   lista->agregarAdicional(2,txtAdB1);
   lista->agregarAdicional(2,txtAdB2);

   static ListaGui listaGui( *lista );
   static FiguraLista flista( &listaGui, area );
   static ComportamientoNewObjetoRectangular cNewL( area, &flista, &listaGui, lista, tabla  );


   Gtk::Button * botonLista = 0;
   builder->get_widget("botonLista", botonLista);
   botonLista->signal_clicked().connect(sigc::bind<Comportamiento*>( sigc::mem_fun( area,&MyArea::setComportamiento), &cNewL ) );

   Gtk::Button * botonEliminarSeleccionado = 0;
   builder->get_widget("button1", botonEliminarSeleccionado);
   botonEliminarSeleccionado->signal_clicked().connect( sigc::mem_fun( area,&MyArea::removeActual) );


}


int main(int arc, char **argv) {

  try {
    // Creo la GUI a partir del .glade  
    Gtk::Main kit( arc, argv );
    Glib::RefPtr<Gtk::Builder> builder;
    builder = Gtk::Builder::create_from_file("gui");

    // Creo un contexto editor
    ContextoEditor ctxEditor;

    // Maximizo ventana principal
    Gtk::Window* window = 0;
    builder->get_widget("windowPrincipal", window);
    window->maximize();

    // Opciones para modificar Doc y DocTemplate
    Gtk::HBox* boxPropiedades;
    builder->get_widget("boxWorkspace", boxPropiedades);



    // Opciones para el editor
    Gtk::HBox* boxEdicion = 0;
    builder->get_widget("boxEdicion", boxEdicion);
    TablaDePropiedades tabla;
    boxEdicion->pack_start( tabla, false, true, 0 );
    tabla.setObjeto( NULL );

    // Agrego un Area de dibujo en el scrolled window.
    MyArea area( &tabla, ctxEditor );
    area.setHoja( NULL );
    area.show();
    area.set_size_request( 700, 700 ); 
    Gtk::HBox boxArea;
    boxArea.pack_start( area );
    boxArea.show();
    ctxEditor.agregarObservador( &area );

    Gtk::ScrolledWindow* scrollWindowArea;
    builder->get_widget("scrolledwindowArea", scrollWindowArea);
    scrollWindowArea->add( boxArea );

   // Creo el Menú principal
    Gtk::HBox* boxMenu;
    builder->get_widget("boxMenu", boxMenu);
    Gtk::VBox vbox;
    boxMenu->pack_start(vbox); 
    crearMenu( vbox, vbox, *window, ctxEditor, &area  );
    vbox.show();

    area.hide();


    ComboVersiones combo( ctxEditor );
    boxPropiedades->pack_start( combo, false, true, 0 );
    combo.show();
    ctxEditor.agregarObservador( &combo );
    combo.notify();
    inicializarHerramientas( &area , builder, tabla );

    kit.run(*window);
  } catch ( const Gtk::BuilderError& ex ) {
    std::cerr << ex.what();
  }

  return 0;
}
