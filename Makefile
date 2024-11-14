IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = fhash.h rwlock.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = fhash.o rwlock.o chash.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
  rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
