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


void playTicTacToe()
{
    int keepPlaying = 1;
    int mode = selectGameMode();

    if (mode == -1)
        return;

    // Track statistics across multiple games
    int xWins = 0, oWins = 0, draws = 0;
    int gamesPlayed = 0;

    while (keepPlaying)
    {
        char board[3][3];
        int row, col;
        char currentPlayer = 'X';
        int movesCount = 0;
        int gameWon = 0;

        initializeTicTacToe(board);

        clearScreen();
        setColor(COLOR_YELLOW);
        printf("\n=== TIC TAC TOE GAME ===\n\n");
        setColor(COLOR_RESET);

        if (mode == 1)
        {
            printf("Player 1: X | Player 2: O\n");
        }
        else
        {
            printf("You: X | Computer: O\n");
        }

        // Display statistics if games have been played
        if (gamesPlayed > 0)
        {
            displayGameStats(xWins, oWins, draws);
        }
        printf("\n");

        while (!gameWon && movesCount < 9)
        {
            displayTicTacToeBoard(board);

            if (currentPlayer == 'O' && mode == 2)
            {
                printf("\nComputer is thinking...\n");
                Sleep(500);
                computerMove(board);
            }
            else
            {
                setColor(COLOR_CYAN);
                printf("\nPlayer %c's turn\n", currentPlayer);
                setColor(COLOR_RESET);
                printf("Enter row (1-3): ");
                if (scanf("%d", &row) != 1)
                {
                    clearInputBuffer();
                    setColor(COLOR_RED);
                    printf("\nInvalid input! Try again.\n");
                    setColor(COLOR_RESET);
                    Sleep(1000);
                    clearScreen();
                    if (gamesPlayed > 0)
                    {
                        setColor(COLOR_YELLOW);
                        printf("\n=== TIC TAC TOE GAME ===\n\n");
                        setColor(COLOR_RESET);
                        if (mode == 1)
                            printf("Player 1: X | Player 2: O\n");
                        else
                            printf("You: X | Computer: O\n");
                        displayGameStats(xWins, oWins, draws);
                        printf("\n");
                    }
                    continue;
                }
                printf("Enter column (1-3): ");
                if (scanf("%d", &col) != 1)
                {
                    clearInputBuffer();
                    setColor(COLOR_RED);
                    printf("\nInvalid input! Try again.\n");
                    setColor(COLOR_RESET);
                    Sleep(1000);
                    clearScreen();
                    if (gamesPlayed > 0)
                    {
                        setColor(COLOR_YELLOW);
                        printf("\n=== TIC TAC TOE GAME ===\n\n");
                        setColor(COLOR_RESET);
                        if (mode == 1)
                            printf("Player 1: X | Player 2: O\n");
                        else
                            printf("You: X | Computer: O\n");
                        displayGameStats(xWins, oWins, draws);
                        printf("\n");
                    }
                    continue;
                }
                clearInputBuffer();

                row--;
                col--;

                if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
                {
                    setColor(COLOR_RED);
                    printf("\nInvalid move! Try again.\n");
                    setColor(COLOR_RESET);
                    Sleep(1000);
                    clearScreen();
                    if (gamesPlayed > 0)
                    {
                        setColor(COLOR_YELLOW);
                        printf("\n=== TIC TAC TOE GAME ===\n\n");
                        setColor(COLOR_RESET);
                        if (mode == 1)
                            printf("Player 1: X | Player 2: O\n");
                        else
                            printf("You: X | Computer: O\n");
                        displayGameStats(xWins, oWins, draws);
                        printf("\n");
                    }
                    continue;
                }

                board[row][col] = currentPlayer;
            }

            movesCount++;

            if (checkWinTicTacToe(board))
            {
                clearScreen();
                displayTicTacToeBoard(board);
                setColor(COLOR_GREEN);
                printf("\n  ====================================\n");
                if (mode == 2 && currentPlayer == 'O')
                {
                    printf("  |       Computer WINS!             |\n");
                    oWins++;
                }
                else if (mode == 2 && currentPlayer == 'X')
                {
                    printf("  |       You WIN!                   |\n");
                    xWins++;
                }
                else
                {
                    printf("  |       Player %c WINS!             |\n", currentPlayer);
                    if (currentPlayer == 'X')
                        xWins++;
                    else
                        oWins++;
                }
                printf("  ====================================\n");
                setColor(COLOR_RESET);
                Beep(800, 200);
                Beep(1000, 300);
                gameWon = 1;
                gamesPlayed++;
            }
            else if (movesCount == 9)
            {
                clearScreen();
                displayTicTacToeBoard(board);
                setColor(COLOR_YELLOW);
                printf("\n  ====================================\n");
                printf("  |       It's a DRAW!               |\n");
                printf("  ====================================\n");
                setColor(COLOR_RESET);
                Beep(500, 300);
                draws++;
                gamesPlayed++;
            }
            else
            {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                clearScreen();
                if (gamesPlayed > 0)
                {
                    setColor(COLOR_YELLOW);
                    printf("\n=== TIC TAC TOE GAME ===\n\n");
                    setColor(COLOR_RESET);
                    if (mode == 1)
                        printf("Player 1: X | Player 2: O\n");
                    else
                        printf("You: X | Computer: O\n");
                    displayGameStats(xWins, oWins, draws);
                    printf("\n");
                }
            }
        }

        // Display final statistics
        printf("\n");
        displayGameStats(xWins, oWins, draws);

        printf("\n");
        setColor(COLOR_CYAN);
        printf("  ====================================\n");
        printf("  |   Play again? (Y/N):             |\n");
        printf("  ====================================\n");
        setColor(COLOR_YELLOW);
        printf("  Your choice: ");
        setColor(COLOR_RESET);

        char response[10];
        if (scanf("%s", response) == 1)
        {
            clearInputBuffer();
            char playAgain = tolower(response[0]);

            if (playAgain == 'y')
            {
                setColor(COLOR_GREEN);
                printf("\n  Starting new game...\n");
                setColor(COLOR_RESET);
                Sleep(800);
            }
            else if (playAgain == 'n')
            {
                clearScreen();
                setColor(COLOR_YELLOW);
                printf("\n  ====================================\n");
                printf("  |  1. Change game mode             |\n");
                printf("  |  2. Return to main menu          |\n");
                printf("  ====================================\n");
                setColor(COLOR_RESET);
                printf("  Your choice: ");

                int exitChoice;
                if (scanf("%d", &exitChoice) == 1)
                {
                    clearInputBuffer();
                    if (exitChoice == 1)
                    {
                        mode = selectGameMode();
                        if (mode == -1)
                        {
                            keepPlaying = 0;
                        }
                        else
                        {
                            xWins = 0;
                            oWins = 0;
                            draws = 0;
                            gamesPlayed = 0;
                            setColor(COLOR_GREEN);
                            printf("\n  Starting new game mode...\n");
                            setColor(COLOR_RESET);
                            Sleep(800);
                        }
                    }
                    else
                    {
                        keepPlaying = 0;
                    }
                }
                else
                {
                    clearInputBuffer();
                    keepPlaying = 0;
                }
            }
            else
            {
                keepPlaying = 0;
            }
        }
        else
        {
            clearInputBuffer();
            keepPlaying = 0;
        }
    }

    // Display final session summary
    if (gamesPlayed > 0)
    {
        clearScreen();
        setColor(COLOR_CYAN);
        printf("\n==========================================\n");
        printf("  |        SESSION SUMMARY                 |\n");
        printf("  ==========================================\n");
        setColor(COLOR_RESET);
        printf("  |  Games Played: %-3d                    |\n", gamesPlayed);
        setColor(COLOR_GREEN);
        printf("  |  X Wins: %-3d                          |\n", xWins);
        setColor(COLOR_RED);
        printf("  |  O Wins: %-3d                          |\n", oWins);
        setColor(COLOR_YELLOW);
        printf("  |  Draws: %-3d                           |\n", draws);
        setColor(COLOR_CYAN);
        printf("  ==========================================\n");
        setColor(COLOR_RESET);
        printf("\n  Press any key to return to main menu...");
        getch();
    }
}


void computerMove(char board[3][3])
{
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';

                if (score > bestScore)
                {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if (moveRow != -1 && moveCol != -1)
    {
        board[moveRow][moveCol] = 'O';
    }
}

