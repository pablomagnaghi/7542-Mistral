#include "server_WebService.h"


#include "./../Xml.h"
#include "common_PeticionHTTP.h"
#include "common_RespuestaHTTP.h"
#include "common_Soap.h"

#include "./../GeneradorPostScript.h"
#include "./../Fecha.h"


void WebService::procesarPeticionSOAP(  PeticionHTTP& peticionSOAP , 
					RespuestaHTTP& respuestaSOAP ) {
  
  int resultadoPostscript = RETURN_SOAP_OK;
  std::string rutaArchivoPostScript;

  Xml xmlRequest;

  try {
    this->validarPeticionHTTPSoap( peticionSOAP, xmlRequest );

    Xml xmlDatos;
    std::string nombreTemplate;
    Fecha fechaValidez;

    this->cargarParametros( xmlRequest, xmlDatos, nombreTemplate, fechaValidez );


    resultadoPostscript = this->procesarDocTemplate(  nombreTemplate,
						      xmlDatos,
						      fechaValidez,
						      rutaArchivoPostScript );

    this->construirRespuesta( resultadoPostscript, 
			      rutaArchivoPostScript, 
			      respuestaSOAP );
  }
  catch ( Exception* ex ){
    respuestaSOAP.setCodigo( CODE_SERVER_ERROR );
    respuestaSOAP.setDescripcion( DESCRIPCION_SERVER_ERROR );
    std::cout << std::endl << ex->getMsjError();
    delete ex;
  }
}


void WebService::validarPeticionHTTPSoap( const PeticionHTTP& p, 
					  Xml&  pXml) {

  std::string bodyStr;
  p.getMessageBody( bodyStr );
  pXml.fromString( bodyStr );
}

int WebService::procesarDocTemplate( const std::string& nombreTemplate, 
				     Xml& xmlDatos, Fecha& fechaTemplate,
				     std::string& archivoCreado ) {

  int resultado = RETURN_SOAP_OK;

  try {
    std::string pathTemplate = "./" + nombreTemplate;
    DocTemplate docLevantado( pathTemplate  );

    std::string tagDeDatos = docLevantado.getXpathNodoDatos();
    Template* versionTemplate = docLevantado.getVersion( fechaTemplate );

    if ( versionTemplate ) {
      GeneradorPostScript generador( versionTemplate, &xmlDatos, tagDeDatos );

      if ( generador.procesar( true ) ) {
	resultado = RETURN_SOAP_OK;
	archivoCreado = tagDeDatos + ".ps";
      }
      else
	resultado = RETURN_SOAP_SIN_TAG_DATOS;
    }
    else {
      resultado = RETURN_SOAP_SIN_VERSION;
    }
  }
  catch ( DocTemplateInvalidoExc* ex ) {
    std::cout << ex->getMsjError();
    resultado = RETURN_SOAP_SIN_TEMPLATE;
    delete ex;
  }
  catch ( DocTemplateArchivoInexistenteExc* ex ) {
    std::cout << ex->getMsjError();
    resultado = RETURN_SOAP_SIN_TEMPLATE;
    delete ex;
  } 
  catch ( Exception* ex ) {
    std::cout << ex->getMsjError();
      delete ex;
  }
  
  return resultado;
}


void WebService::cargarParametros(  Xml& xmlSoapReq, Xml& datos, 
				    std::string& plantilla, Fecha& fecha ) {

  XmlNodo* raiz = xmlSoapReq.getNodoRaiz();

  XmlNodo::verificarNombre( "Envelope", *raiz );

  XmlNodo nodoHijo = raiz->getHijo();

  while ( (nodoHijo.esValido()) && (nodoHijo.getNombre()!="Body") ) {
    nodoHijo = nodoHijo.getHermano();
  }

  if ( ( nodoHijo.esValido() ) && (nodoHijo.getNombre()=="Body") ) {
    XmlNodo nodoParam1 = nodoHijo.getHijo();
    XmlNodo nodoParam2 = nodoParam1.getHermano();
    XmlNodo nodoParam3 = nodoParam2.getHermano();

    XmlNodo::verificarNombre( "nombreTemplate", nodoParam1 );
    XmlNodo::verificarNombre( "fechaValidez", nodoParam2 );
    XmlNodo::verificarNombre( "archivoDatos", nodoParam3 );


    plantilla = nodoParam1.getContenido();

    Fecha fechaTemplate( nodoParam2.getContenido() );
    if ( !fechaTemplate.esValida() )
      throw new FechaInvalidaException();
    fecha = fechaTemplate;

    datos.fromString( nodoParam3.getContenido() );
  }
  else {
    throw new SOAPInvalidoExc();
  }
}

void WebService::construirRespuesta(  int codeReturn, 
				      const std::string& archivoCreado,
				      RespuestaHTTP& respuestaSOAP ) {

  
  Xml respuestaXmlSoap;
  Soap respuesta( respuestaXmlSoap );

  XmlNodo nodoResultado("codeReturn");
  nodoResultado.setContenido( codeReturn );
  respuesta.agregarHijoBody(nodoResultado);

  XmlNodo nodoNombreArchivo("nombreArchivoResultado");
  nodoNombreArchivo.setContenido( archivoCreado );
  respuesta.agregarHijoBody(nodoNombreArchivo);

  respuestaSOAP.clear();
  respuestaSOAP.setCodigo( CODE_OK );
  respuestaSOAP.setDescripcion( DESCRIPCION_OK );

  std::string responseBody;
  respuestaXmlSoap.toString( responseBody );
  respuestaSOAP.setMessageBody( responseBody );
}
