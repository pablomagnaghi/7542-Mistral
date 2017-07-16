#ifndef HOJA_H_
#define HOJA_H_

#include "ObjetoGraficoRectangular.h"
#include <list>
#include "XmlNodo.h"

class Visitor;

class Hoja : public ObjetoGraficoRectangular {
private:
  std::string tipoHoja;
  std::list<ObjetoGrafico*> misObjetos;

  void obtenerObjetosGraficos ( XmlNodo* );

protected:
  // redefinidos para agregar borde
  virtual void agregarAtributos ( XmlNodo* );
  virtual void obtenerAtributos ( XmlNodo* );

public:
  Hoja( int ancho, int alto, const std::string& tipoLetra );
  Hoja();
  Hoja( XmlNodo* );
  ObjetoGraficoRectangular* clone();
  virtual ~Hoja();

  void agregarObjeto( ObjetoGrafico* );
  void removeObjeto( ObjetoGrafico*  );
  std::list<ObjetoGrafico*>::iterator listaBegin();

  std::list<ObjetoGrafico*>::iterator listaEnd();

  void accept( Visitor* v );

  std::string getTipoHoja() const;
  void setTipoHoja( const std::string& tipoHoja );

  XmlNodo toXml();
};

#endif /* HOJA_H_ */

