CC=gcc
CFLAGS=-I. -g
DEPS = calendar.h
OBJ = calendar.o count.o print.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

calendar: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
