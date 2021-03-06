# Makefile de ejemplo para C++
#
# Creado: jue abr 15 15:34:19 ART 2004
#
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
#

# CONFIGURACION
################

# Nombre del ejecutable.
target = psGui

# ExtensiÃ³n de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Archivos con el cÃ³digo fuente que componen el ejecutable. Si no se especifica,
# toma todos los archivos con la extensiÃ³n mencionada. Para especificar hay que
# descomentar la lÃ­nea (quitarle el '#' del principio).
# NOTA: No poner cabeceras (.h).
fuentes += $(wildcard *.$(extension))

fuentes +=  ./../Calculo.cpp  ./../Linea.cpp ./../OperandoVariable.cpp ./../TextoVariable.cpp
 fuentes +=  ./../Columna.cpp ./../ParseadorArgumentos.cpp  ./../VisitorPostScript.cpp
 fuentes +=  ./../DocTemplate.cpp ./../ObjetoGrafico.cpp ./../ParseadorRPN.cpp ./../Xml.cpp
 fuentes +=  ./../ElementoDeCalculo.cpp  ./../ObjetoGraficoRectangular.cpp  ./../PostScript.cpp
 fuentes +=  ./../Fecha.cpp ./../ObjetoLista.cpp ./../Template.cpp    ./../XmlNodo.cpp
fuentes +=  ./../GeneradorPostScript.cpp  ./../Operador.cpp  ./../Texto.cpp
fuentes += ./../Hoja.cpp ./../OperandoConstante.cpp ./../TextoFijo.cpp   ./../XmlNodeSet.cpp



# Si usa funciones de math.h, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
math = si

# Si usa pthreads, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
#pthreads = si

# Si usa gthreads, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
#gthreads = si

# Si es un programa GTK+, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
#gtk = si

# Si es un programa gtkmm, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
gtkmm = si

# Si se usa libxml, descomentÃ¡ (quitale el '#' a) la siguiente lÃ­nea.
libxml = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si


# CONFIGURACION "AVANZADA"
###########################


# Opciones para el compilador C/C++ en modo ansi.
#CFLAGS = -Wall -pedantic -pedantic-errors
CFLAGS = -Wall 

# Para que explote lo mas posible
CFLAGS += -O3 -DNDEBUG

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Opciones del enlazador.
#LDFLAGS =

# Estandar de C a usar
CSTD = c99

# Estandar de C++ a usar
CXXSTD = c++98

# Si se quiere compilar estaticamente, descomentar la siguiente linea
#static = si


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-2.0)
LDFLAGS += $(shell pkg-config --libs gtk+-2.0)
endif

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtkmm
CFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
LDFLAGS += $(shell pkg-config --libs gtkmm-2.4)
endif

# Agrego flags y libs de gthreads de ser necesario.
ifdef gthreads
CFLAGS += $(shell pkg-config --cflags gthread-2.0)
LDFLAGS += $(shell pkg-config --libs gthread-2.0)
endif

# Linkeo con libm de ser necesario.
ifdef math
LDFLAGS += -lm
endif

# Linkeo con pthreads de ser necesario.
ifdef pthreads
LDFLAGS += -lpthread -pthread
endif

# Agrego flags y libs de libxml de ser necesario.
ifdef libxml
CFLAGS += $(shell pkg-config --cflags libxml-2.0)
LDFLAGS += $(shell pkg-config --libs libxml-2.0)
endif


ifdef static
LDFLAGS += -static
endif

# Pongo flags de C para C++ tambiÃ©n
CXXFLAGS += $(CFLAGS)

# Uso enlazador de c++ si es cÃ³digo no C.
ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

# Si no especifica archivos, tomo todos.
# fuentes ?= $(wildcard *.$(extension))

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif


# REGLAS
#########

.PHONY: all clean

all: $(target)

o_files = $(patsubst %.$(extension),%.o,$(fuentes))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_files:.o=.deps)

$(target): $(o_files)
	@if [ -z "$(o_files)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensiÃ³n debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_files) $(LOADLIBS) $(LDLIBS) -o $(target)

clean:
	$(RM) $(o_files) $(o_files:.o=.deps) $(target)



