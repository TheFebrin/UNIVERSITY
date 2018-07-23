CC = gcc
CFLAGS = -g -O -std=gnu11 -Wall -Wextra 
LIBS = -lncurses

maze: main.o
	$(CC) $(CFLAGS) main.o -o maze $(LIBS)

main.o: main.c funkcje.h struktury.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm main.o maze