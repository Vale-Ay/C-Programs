CC=gcc
CFLAGS=-I.
DEPS = pa4.h

OBJ = main.o handle.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pa4: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

