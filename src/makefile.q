IDIR = ../include

CC=gcc
CFLAGS=-g -std=c89 -ansi -Wall -Werror -pedantic -D_DEBUG -I$(IDIR)

ODIR=obj

LDIR = ../lib
LIBS=-L$(LDIR)

all:circ_q_test

_DEPS = circ_q.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = circ_q.o circ_q_test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

	
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

	
circ_q_test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
.PHONY:clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

