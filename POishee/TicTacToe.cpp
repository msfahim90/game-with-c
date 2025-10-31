/*
 tic_tac_toe_dev1.c
 Standalone Tic-Tac-Toe for Developer 1
 Author: extracted & cleaned version for dev1
 Compile (Windows/MinGW): gcc tic_tac_toe_dev1.c -o tic_tac_toe_dev1.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    // _getch(), _kbhit()
#include <windows.h>  // Sleep()

char tttBoard[3][3];
int tttGameOver;

void setupTicTacToe();
void drawTicTacToe();
int checkWinner();
int findWinningMove(char player);
int findBlockingMove();
void computerMove();
void clearInputBuffer();

void clearInputBuffer() {
    while (getchar() != '\n' && !feof(stdin));
}

void setupTicTacToe() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tttBoard[i][j] = ' ';
    tttGameOver = 0;
}

void drawTicTacToe() {
    system("cls");
    printf("\n\n  ====================================\n");
    printf("          TIC TAC TOE\n");
    printf("  ====================================\n\n");
    printf("       %c | %c | %c \n", tttBoard[0][0], tttBoard[0][1], tttBoard[0][2]);
    printf("      -----------\n");
    printf("       %c | %c | %c \n", tttBoard[1][0], tttBoard[1][1], tttBoard[1][2]);
    printf("      -----------\n");
    printf("       %c | %c | %c \n", tttBoard[2][0], tttBoard[2][1], tttBoard[2][2]);
    printf("\n  ====================================\n");
}

int checkWinner() {
    // Rows and columns
    for (int i = 0; i < 3; i++) {
        if (tttBoard[i][0] == tttBoard[i][1] && tttBoard[i][1] == tttBoard[i][2] && tttBoard[i][0] != ' ')
            return (tttBoard[i][0] == 'X') ? 1 : 2;
        if (tttBoard[0][i] == tttBoard[1][i] && tttBoard[1][i] == tttBoard[2][i] && tttBoard[0][i] != ' ')
            return (tttBoard[0][i] == 'X') ? 1 : 2;
    }
    // Diagonals
    if (tttBoard[0][0] == tttBoard[1][1] && tttBoard[1][1] == tttBoard[2][2] && tttBoard[0][0] != ' ')
        return (tttBoard[0][0] == 'X') ? 1 : 2;
    if (tttBoard[0][2] == tttBoard[1][1] && tttBoard[1][1] == tttBoard[2][0] && tttBoard[0][2] != ' ')
        return (tttBoard[0][2] == 'X') ? 1 : 2;

    // Check for any empty cell
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tttBoard[i][j] == ' ') return 0;
    return 3; // Draw
}

/* Find a winning move for 'player' (either 'X' or 'O').
   Returns move index 0..8 (row*3 + col) or -1 if none. */
int findWinningMove(char player) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tttBoard[i][j] == ' ') {
                tttBoard[i][j] = player;
                int win = 0;
                // check row
                if (tttBoard[i][0] == player && tttBoard[i][1] == player && tttBoard[i][2] == player) win = 1;
                // check column
                if (tttBoard[0][j] == player && tttBoard[1][j] == player && tttBoard[2][j] == player) win = 1;
                // diag
                if (i == j && tttBoard[0][0] == player && tttBoard[1][1] == player && tttBoard[2][2] == player) win = 1;
                if (i + j == 2 && tttBoard[0][2] == player && tttBoard[1][1] == player && tttBoard[2][0] == player) win = 1;
                tttBoard[i][j] = ' ';
                if (win) return i * 3 + j;
            }
        }
    }
    return -1;
}

int findBlockingMove() {
    return findWinningMove('X'); // block X
}

/* Simple AI for computer (plays 'O'):
   1) Win if possible
   2) Block opponent's win
   3) Take center
   4) Take a corner
   5) Take any side */
void computerMove() {
    int move = findWinningMove('O');    // try to win
    if (move == -1) move = findBlockingMove(); // block X

    if (move == -1 && tttBoard[1][1] == ' ') move = 4; // center

    if (move == -1) {
        int corners[] = {0, 2, 6, 8};
        for (int i = 0; i < 4; i++) {
            int r = corners[i] / 3;
            int c = corners[i] % 3;
            if (tttBoard[r][c] == ' ') { move = corners[i]; break; }
        }
    }

    if (move == -1) {
        int sides[] = {1, 3, 5, 7};
        for (int i = 0; i < 4; i++) {
            int r = sides[i] / 3;
            int c = sides[i] % 3;
            if (tttBoard[r][c] == ' ') { move = sides[i]; break; }
        }
    }

    if (move == -1) { // fallback: first empty
        for (int i = 0; i < 9; i++) {
            int r = i / 3, c = i % 3;
            if (tttBoard[r][c] == ' ') { move = i; break; }
        }
    }

    if (move != -1) {
        int r = move / 3, c = move % 3;
        tttBoard[r][c] = 'O';
    }
}

void ticTacToe() {
    char again;
    do {
        system("cls");
        printf("\n\n  ====================================\n");
        printf("       TIC TAC TOE - MODE\n");
        printf("  ====================================\n\n");
        printf("  1. Player vs Player\n");
        printf("  2. Player vs Computer\n\n");
        printf("  ====================================\n");
        printf("\n  Select mode (1-2): ");

        int mode;
        if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
            clearInputBuffer();
            printf("\n  Invalid selection. Press any key to continue...");
            _getch();
            continue;
        }
        clearInputBuffer();

        setupTicTacToe();
        int player = 1; // 1 -> X, 2 -> O
        int winner = 0;

        while (!winner) {
            drawTicTacToe();

            if (mode == 2 && player == 2) {
                printf("\n  Computer is thinking...\n");
                Sleep(600);
                computerMove();
                winner = checkWinner();
                if (!winner) player = 1;
            } else {
                int r, c;
                printf("\n  Player %d (%c), row (1-3): ", player, (player == 1) ? 'X' : 'O');
                if (scanf("%d", &r) != 1 || r < 1 || r > 3) {
                    clearInputBuffer();
                    printf("\n  Invalid input. Press any key...");
                    _getch();
                    continue;
                }
                printf("  Player %d (%c), col (1-3): ", player, (player == 1) ? 'X' : 'O');
                if (scanf("%d", &c) != 1 || c < 1 || c > 3) {
                    clearInputBuffer();
                    printf("\n  Invalid input. Press any key...");
                    _getch();
                    continue;
                }
                clearInputBuffer();

                r--; c--;
                if (tttBoard[r][c] != ' ') {
                    printf("\n  Cell already taken. Press any key...");
                    _getch();
                    continue;
                }

                tttBoard[r][c] = (player == 1) ? 'X' : 'O';
                winner = checkWinner();
                if (!winner) player = (player == 1) ? 2 : 1;
            }
        }

        drawTicTacToe();

        if (winner == 3) {
            printf("\n  It's a Draw!\n");
        } else if (mode == 2 && winner == 2) {
            printf("\n  Computer wins!\n");
        } else {
            printf("\n  Player %d wins!\n", winner);
        }

        printf("\n  Play again? (Y/N): ");
        again = _getch();
        // consume possible newline
        clearInputBuffer();
    } while (again == 'y' || again == 'Y');
}

int main() {
    ticTacToe();
    return 0;
}
