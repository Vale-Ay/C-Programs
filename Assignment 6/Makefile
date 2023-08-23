CC=gcc
CFLAGS=-I. -g -w -pthread -lm
DEPS = buff.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

reverse: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


