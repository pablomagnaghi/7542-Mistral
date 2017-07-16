#include "XmlNodeSet.h"

#include <libxml/xpath.h>
#include "XmlNodo.h"

XmlNodeSet::XmlNodeSet( xmlXPathObjectPtr result ) : result(result) {

}

int XmlNodeSet::size() {
  return result->nodesetval->nodeNr;
}

XmlNodo XmlNodeSet::getNodo( int pos ) {
  if ( (pos<0) && (pos>=result->nodesetval->nodeNr) ) {
	throw new IndexFueraDeRangoEnNodeSetExc( size(), pos );
  }
  return result->nodesetval->nodeTab[pos];
}

XmlNodeSet::~XmlNodeSet() {
  if( !xmlXPathNodeSetIsEmpty( result->nodesetval) ) {
	//xmlXPathFreeNodeSet( result->nodesetval );
    xmlXPathFreeObject(result);
  }
}
