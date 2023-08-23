CC=gcc
CFLAGS=-I.
DEPS = chess.h
OBJ = show.o capture.o move.o chess.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
