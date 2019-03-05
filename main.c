#include "board.h"
#include "display.h"

int main(int argc, char* argv[]) {
	Board *board = newBoard();
	printBoard(board);
	int x;
	int y;
	char turn = 'b';
	scanf("%d", &x);
	while(x != -1) {
		scanf("%d", &y);
		printf("loop");
		placePiece(board, y, x, turn);
		printBoard(board);
		if(turn == 'b') { turn = 'w';}
		else if(turn == 'w') { turn = 'b';}
		scanf("%d",&x);
	}
	return 0;
}
