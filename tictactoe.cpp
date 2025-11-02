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



int selectGameMode()
{
    clearScreen();
    setColor(COLOR_YELLOW);
    printf("\n=== TIC TAC TOE - SELECT MODE ===\n\n");
    setColor(COLOR_RESET);
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    printf("3. Back to Main Menu\n\n");
    printf("Enter choice (1-3): ");

    int choice;
    if (scanf("%d", &choice) != 1)
    {
        clearInputBuffer();
        return 1;
    }
    clearInputBuffer();

    if (choice == 3)
        return -1;
    if (choice < 1 || choice > 3)
        return 1;
    return choice;
}

