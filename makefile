PROGRAMA = main.c
EJECUTABLE = programa
INTERPRETE = interprete.c
CARPETACONJUNTOS = conjuntos/
CARPETAARBOL = $(CARPETACONJUNTOS)arbolIntervalo/
CARPETAHASH = $(CARPETACONJUNTOS)hashSlist/
ARBOL = arbolIntervalo.o
INTERVALO = intervalo.o
TABLA = tablahash.o
SLIST = slist.o
CONJUNTOS = conjunto
BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: programa 

programa: $(PROGRAMA) $(INTERPRETE:.c=.o) $(CONJUNTOS)
	gcc -o $(EJECUTABLE) $(PROGRAMA) $(INTERPRETE:.c=.o) $(CARPETAARBOL)$(ARBOL) $(CARPETAARBOL)$(INTERVALO:.c=.o) $(CARPETAHASH)$(TABLA:.c=.o) $(CARPETAHASH)$(SLIST:.c=.o) $(CARPETACONJUNTOS)$(CONJUNTOS).o $(BANDERAS)
$(INTERPRETE:.c=.o): $(INTERPRETE) $(INTERPRETE:.c=.h)
	gcc -c $(BANDERAS) $(INTERPRETE)
$(CONJUNTOS):
	cd $(CARPETACONJUNTOS) && make
clean: 
	rm *.o