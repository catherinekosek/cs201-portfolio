# Othello
  Portfolio Project for CS 201
  
## Description
  Othello, also known as Reversi, is a board game traditionally played on an 8x8 game board. Players take turns placing pieces of their color, black or white, on the board. A piece must be placed in a horizontal, vertical, or diagonal line from another piece of the same color, and there must be no empty spaces and one or more contiguous pieces of the opposite color between the existing piece and the newly placed piece. These sandwhiched pieces of the opposite color are flipped. The game ends when neither player can make any more moves, and the winner is the player with the most pieces of their color on the board.

## Program Functionality 
### Interface
  ASCII based
### Game Modes
  Two Player - two people play against each other, passing the game back and forth for each turn <br>
  Easy - one person plays against an AI utilizing the "easy" strategy detailed in the AI section <br>
  Regular - one person plays against an AI utilizing the "regular" strategy detailed in the AI section <br>
### Rematches
  Once a game is over, the user can opt to play against against the same opponent on the same board size. The players swap pieces and who starts first. Wins are kept track across games. <br>
  The user can also opt to start a different game and reselect the opponent and board size. Wins are reset.
### Board Size
  The recommended, traditional game board size is 8x8. However, game boards can be any multiple of four greater than or equal to 8. Game boards are always square. <br>
  Large boards will not display correctly on the screen. A game board larger than 40x40 is not recommended, although larger boards might still display correctly depending on screen size. <br>
  Extremely large boards, like 40000x40000, will slow the program down considerably. If there is not enough space available for an extremely large board, the program will crash. <br>

## Program Input
  Program input is read in 20 characters at a time. Character input must be entered all lowercase exactly as options appear, followed by a single press of the Enter key. Number input, like entered board size or location, must be entered in numeric digits, followed by a single press of the Enter key. <br>
  If input entered is longer than 20 characters, the input will be read in 20 character segments and the program will respond to each 20 character segment appropriately. This means that an invalid 80 character input will be read in four segments, so an invalid input message will appear four times. Long inputs will not crash the program, but the output is odd. The only exception is entering a valid but extremely large board size, which may crash the program if not enough space is available. <br>
  At any time prompted for input, the user can enter "instructions", "help", or "quit" followed by a single press of the Enter key. "instructions" will display gameplay instructions. "help" displays tips detailing correct input for the current input requested. Help will display differnt help instructions at different points in the program. "quit" will end program execution. If "instructions" or "help" is entered, the game returns to prompting for the initially requested input immediately after printing the instructions or help. <br> 

## Overview of Files
othello <br>
  Program executable 
  
makefile <br>
  Compiles all files to create othello program executable.

coordinate.c <br>
  Utility struct for storing a location r, c. Also used by the AI for storing the value of making a move at r, c.
  
player.c <br>
  Player struct with attributes name, type, wins, and moveExists (whether or not there is a valid move available for the Player). If the type of the player is an AI, Coordinate nextMove contains the location r,c of the move to be taken. If the type of the player is a regular AI, moveWeights contains an array of the strategic value of each location on the board.
  
board.c <br>
  Board struct with attributes size, whitePieces, and blackPieces. The actual gameboard is represented in an array called boardArray. Valid moves on the board are calculated for a specific Player and stored in validMoves. The array visited is a utilty array used during the depth-first-search.
  All of the complex and recursive gameplay logic is performed by methods in this file. placePiece calls the recursive method flipPieces eight times, once for each direction, to perform the appropriate piece color flips when a new piece is placed on the board. checkForMoves begins a depth-first search of the board for pieces for the current turn. Once a piece of that turn's color is found, the recursive method findMoves is called eight times, once for each direction, to search for an empty square that creates a valid move.
  
game.c <br>
  Game struct with a pointer to a Board, a pointer to each Player, and a third additional Player pointer indicating whose turn it is.
  Control logic for the flow of the game is performed by methods in this file. playGame contains a loop that continues taking turns using either takeHumanTurn or takeAITurn until checkForWin indicates that the game is over. The user is then prompted for a rematch, and, if indicated, the method rematch resets the board and swaps the players for a second game.

input.c <br>
  Handles any input required. Although the game and board classes contain some output statements, input is only read in by methods in this file. Also contains most output, particularly longer messages like menu options, help, and instructions.
  
othello.c <br>
  Contains the main method for the program.
 
## AI Logic 
### Easy
  The "easy" play-against-computer mode follows the Maximum Disk Strategy: make the move that flips the maximum pieces. This strategy is the most inuitive and mimics how new players often choose to make moves. However, this method of gameplay is relatively ineffective. Flipping more disks, especially early in the game, simply offers your opponent more options for strategic gameplay. Also, disks flipped early in the game and in the center of the board are not stable, and therefore do not matter.
  
### Regular
  The "regular" play-against-computer mode follows the Weighted Square Strategy: make the move in the most strategic location. The number of pieces flipped is not considered, as better positioning on the board will result in larger gains towards the end of the game, even if the computer appears to be "losing" at the beginning. Each square has a value assigned to it, indicating its strategic value. The different types of squares, in order from least valuable (worst) to most valuable (best) are: <br>
    1.	X-Squares - diagonally adjacent to a corner - creates easiest opponent access to corners <br>
    2.	C-Squares – vertically or horizontally adjacent to a corner - creates opponent access to corners <br>
    3.	Danger Zone – rows and columns immediately inside the edge rows and columns - creates opponent access to edges <br>
    4.	Internal Squares – internal locations not otherwise specified - not harmful but not particularly advantageous <br>
    5.	Internal Edges – edge locations not otherwise specified - can only be flipped if opponent has position on the same edge <br>
    6.	Internal Corners – diagonally adjacent to the X-squares - creates access to corners <br>
    7.	Edges – vertically or horizontally adjacent to C-squares - creates access to corners and can only be flipped if opponent has position on the same edge <br>
     8.	Corners – four corner squares - once placed, cannot be flipped <br>
  This strategy is optimal on a traditional 8x8 board. Most of this strategy involves making moves along the edges, and it takes awhile for gameplay to reach the edges on a large board. Therefore, the larger the board, the less challenging this strategy becomes. 
