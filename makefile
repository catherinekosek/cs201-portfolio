CC = gcc
CFLAGS = -Wall

all: othello

othello: othello.o input.o game.o board.o player.o coordinate.o
	$(CC) $(CFLAGS) -o othello othello.o input.o game.o board.o player.o coordinate.o

othello.o: othello.c input.h game.h
	$(CC) $(CFLAGS) -c othello.c 

input.o: input.c input.h coordinate.h
	$(CC) $(CFLAGS) -c input.c

game.o: game.c game.h input.h board.h player.h coordinate.h
	$(CC) $(CFLAGS) -c game.c

board.o: board.c board.h player.h 
	$(CC) $(CFLAGS) -c board.c

player.o: player.c player.h coordinate.h
	$(CC) $(CFLAGS) -c player.c

coordinate.o: coordinate.c coordinate.h
	$(CC) $(CFLAGS) -c coordinate.c

clean:
	$(RM) othello *.o

