CC=gcc
CFLAGS=-I.
DEPS = pa5.h
OBJ = main.o conversion.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pa5: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
