#ifndef  _WEB_SERVICE_H_INCLUDED_
#define _WEB_SERVICE_H_INCLUDED_

#include "./../Xml.h"
#include "common_PeticionHTTP.h"
#include "common_RespuestaHTTP.h"
#include "./../Fecha.h"

#define RETURN_SOAP_OK			0
#define RETURN_SOAP_SIN_VERSION		1
#define RETURN_SOAP_SIN_TAG_DATOS	2
#define RETURN_SOAP_SIN_TEMPLATE	3

class WebService {
private:
      
  int procesarDocTemplate(  const std::string& nombreTemplate, 
			    Xml& xmlDatos, Fecha& fechaTemplate,
			    std::string& archivoCreado );

  void construirRespuesta( int codeReturn, const std::string& archivoCreado,
			   RespuestaHTTP& respuestaSOAP );

  void validarPeticionHTTPSoap( const PeticionHTTP&, Xml& peticionSOAP );

  void cargarParametros(  Xml& xmlSoapReq, Xml& datos, 
			  std::string& plantilla, Fecha& );
public:

  void procesarPeticionSOAP( PeticionHTTP& peticionSOAP , RespuestaHTTP& respuestaSOAP );
};

#endif
