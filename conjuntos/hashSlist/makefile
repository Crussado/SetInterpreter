TABLAHASH = tablahash.c
SLIST = slist.c
BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: $(TABLAHASH:.c=.o)

$(TABLAHASH:.c=.o): $(TABLAHASH) $(TABLAHASH:.c=.h) $(SLIST:.c=.o)
	gcc -c $(BANDERAS) $(TABLAHASH)
$(SLIST:.c=.o): $(SLIST) $(SLIST:.c=.h)
	gcc -c $(BANDERAS) $(SLIST)
clean: 
	rm *.o