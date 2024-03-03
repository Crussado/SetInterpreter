INTERVALO = intervalo.c
ITREE = arbolIntervalo.c

BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: $(ITREE:.c=.o) 

$(ITREE:.c=.o): $(ITREE) $(ITREE:.c=.h) $(INTERVALO:.c=.o)
	gcc -c $(BANDERAS) $(ITREE)
$(INTERVALO:.c=.o): $(INTERVALO) $(INTERVALO:.c=.h)
	gcc -c $(BANDERAS) $(INTERVALO)
clean: 
	rm *.o