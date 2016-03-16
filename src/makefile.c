IDIR = ../include

CC=gcc
CFLAGS=-g -pthread -std=c89 -ansi -Wall -Werror -pedantic -D_DEBUG -I$(IDIR)

ODIR=obj

LDIR = ../lib
LIBS=-L$(LDIR)

all:prod_cons_test

_DEPS = circ_q.h prod_cons.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = circ_q.o prod_cons.o prod_cons_test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

	
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

	
prod_cons_test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
.PHONY:clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

