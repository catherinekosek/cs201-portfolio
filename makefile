CC = gcc
CFLAGS = -Wall

all: othello

othello: othello.o board.o player.o game.o input.o coordinate.o
	$(CC) $(CFLAGS) -o othello othello.o board.o player.o game.o input.o coordinate.o

othello.o: othello.c 
	$(CC) $(CFLAGS) -c othello.c 

game.o: game.c game.h board.h player.h input.h
	$(CC) $(CFLAGS) -c game.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

coordinate.o: coordinate.c coordinate.h
	$(CC) $(CFLAGS) -c coordinate.c

clean:
	$(RM) main *.o

