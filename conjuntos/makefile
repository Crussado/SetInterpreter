CARPETAARBOL = arbolIntervalo/
CARPETAHASH = hashSlist/
ARBOL = arbolIntervalo.o
INTERVALO = intervalo.o
TABLA = tablahash.o
SLIST = slist.o
CONJUNTOS = conjunto
BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: $(CONJUNTOS)

$(CONJUNTOS): $(CONJUNTOS).c $(CONJUNTOS).h $(TABLA) $(ARBOL)
	gcc -c $(CONJUNTOS).c $(BANDERAS)
$(TABLA):
	cd $(CARPETAHASH) && make
$(ARBOL):
	cd $(CARPETAARBOL) && make
clean: 
	rm *.o