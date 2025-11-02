/*
 * Tic-Tac-Toe Game Implementation
 * Features:
 * - Player vs Player mode
 * - Player vs Computer mode (with AI using Minimax algorithm)
 * - Session statistics tracking
 * - Colorful UI with game stats display
 */

#include "common.h"

// Function prototypes
void initializeTicTacToe(char board[3][3]);
void displayTicTacToeBoard(char board[3][3]);
int checkWinTicTacToe(char board[3][3]);
void computerMove(char board[3][3]);
int minimax(char board[3][3], int depth, int isMaximizing);
int selectGameMode();
void displayGameStats(int xWins, int oWins, int draws);
