CC = gcc
CFLAGS = -Wall

all: main

main: main.o board.o validMoves.o game.o player.o
	$(CC) $(CFLAGS) -o main main.o board.o validMoves.o game.o player.o

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c

game.o: game.c game.h validMoves.h board.h player.h
	$(CC) $(CFLAGS) -c game.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c

validMoves.o: validMoves.c validMoves.h board.h
	$(CC) $(CFLAGS) -c validMoves.c

clean:
	$(RM) main *.o

