CC = gcc
CFLAGS = -Wall

all: main

main: main.o board.o player.o game.o input.o
	$(CC) $(CFLAGS) -o main main.o board.o player.o game.o input.o

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

game.o: game.c game.h board.h player.h input.h
	$(CC) $(CFLAGS) -c game.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

player.o: player.c player.h board.h
	$(CC) $(CFLAGS) -c player.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

clean:
	$(RM) main *.o

