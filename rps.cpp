/*
 * Rock Paper Scissors Game Implementation
 * Features:
 * - Player vs Computer mode with AI
 * - Player vs Player mode
 * - Session statistics tracking
 * - Win rate calculation
 * - Colorful animated game flow
 */

#include "common.h"

// Function prototypes
void playVsComputer();
void playVsPlayer();
void displayRPSStats(int player1Score, int player2Score, int draws, char *p1Name, char *p2Name);
int getPlayerRPSChoice(char *playerName);
int determineWinner(int choice1, int choice2);
const char *getChoiceName(int choice);

const char *getChoiceName(int choice)
{
    switch (choice)
    {
    case 1:
        return "ROCK";
    case 2:
        return "PAPER";
    case 3:
        return "SCISSORS";
    default:
        return "UNKNOWN";
    }
}


void displayRPSStats(int player1Score, int player2Score, int draws, char *p1Name, char *p2Name)
{
    setColor(COLOR_CYAN);
    printf("\n  ============================================\n");
    printf("  |         MATCH STATISTICS                 |\n");
    printf("  ============================================\n");
    setColor(COLOR_RESET);
    printf("  |  ");
    setColor(COLOR_GREEN);
    printf("%s: %d", p1Name, player1Score);
    setColor(COLOR_RESET);
    printf("  |  ");
    setColor(COLOR_RED);
    printf("%s: %d", p2Name, player2Score);
    setColor(COLOR_RESET);
    printf("  |  ");
    setColor(COLOR_YELLOW);
    printf("Draws: %d", draws);
    setColor(COLOR_RESET);
    printf("  |\n");
    setColor(COLOR_CYAN);
    printf("  ============================================\n");
    setColor(COLOR_RESET);
}


int getPlayerRPSChoice(char *playerName)
{
    int choice;
    setColor(COLOR_GREEN);
    printf("\n  %s, choose your move:\n", playerName);
    setColor(COLOR_RESET);
    printf("  1. Rock\n");
    printf("  2. Paper\n");
    printf("  3. Scissors\n");
    printf("  4. Return to Menu\n\n");
    printf("  Your choice (1-4): ");

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
    {
        clearInputBuffer();
        return -1;
    }
    clearInputBuffer();
    return choice;
}


int determineWinner(int choice1, int choice2)
{
    if (choice1 == choice2)
    {
        return 0; // Draw
    }
    else if ((choice1 == 1 && choice2 == 3) ||
             (choice1 == 2 && choice2 == 1) ||
             (choice1 == 3 && choice2 == 2))
    {
        return 1; // Player 1 wins
    }
    else
    {
        return 2; // Player 2 wins
    }
}


void playVsComputer()
{
    int playerScore = 0, computerScore = 0, draws = 0;
    int gamesPlayed = 0;
    char playerName[] = "You";
    char computerName[] = "Computer";

    clearScreen();
    setColor(COLOR_YELLOW);
    printf("\n  ============================================\n");
    printf("  |        PLAYER VS COMPUTER                |\n");
    printf("  ============================================\n");
    setColor(COLOR_RESET);
    printf("\n  Rules:\n");
    printf("  - Rock beats Scissors\n");
    printf("  - Paper beats Rock\n");
    printf("  - Scissors beats Paper\n\n");
    printf("  Press any key to start...");
    getch();

    while (1)
    {
        clearScreen();
        setColor(COLOR_YELLOW);
        printf("\n  ============================================\n");
        printf("  |        PLAYER VS COMPUTER                |\n");
        printf("  ============================================\n");
        setColor(COLOR_RESET);

        if (gamesPlayed > 0)
        {
            displayRPSStats(playerScore, computerScore, draws, playerName, computerName);
        }

        int playerChoice = getPlayerRPSChoice(playerName);

        if (playerChoice == 4)
        {
            if (gamesPlayed > 0)
            {
                clearScreen();
                setColor(COLOR_CYAN);
                printf("\n  ============================================\n");
                printf("  |          SESSION SUMMARY                 |\n");
                printf("  ============================================\n");
                setColor(COLOR_RESET);
                printf("  |  Games Played: %d\n", gamesPlayed);
                displayRPSStats(playerScore, computerScore, draws, playerName, computerName);

                if (gamesPlayed > 0)
                {
                    int winRate = (playerScore * 100) / gamesPlayed;
                    setColor(COLOR_MAGENTA);
                    printf("\n  Your Win Rate: %d%%\n", winRate);
                    setColor(COLOR_RESET);
                }

                printf("\n  Press any key to return to menu...");
                getch();
            }
            return;
        }

        if (playerChoice == -1)
        {
            setColor(COLOR_RED);
            printf("\n  Invalid choice! Press any key...");
            setColor(COLOR_RESET);
            getch();
            continue;
        }

        int computerChoice = (rand() % 3) + 1;

        printf("\n  ");
        setColor(COLOR_YELLOW);
        printf("Computer is choosing...");
        setColor(COLOR_RESET);
        Sleep(300);
        printf("\n  Rock... Paper... Scissors... SHOOT!\n\n");
        Sleep(500);

        // Display choices
        setColor(COLOR_CYAN);
        printf("  You chose: ");
        setColor(COLOR_GREEN);
        printf("%s\n", getChoiceName(playerChoice));
        setColor(COLOR_CYAN);
        printf("  Computer chose: ");
        setColor(COLOR_RED);
        printf("%s\n\n", getChoiceName(computerChoice));
        setColor(COLOR_RESET);

        int result = determineWinner(playerChoice, computerChoice);

        if (result == 0)
        {
            draws++;
            setColor(COLOR_YELLOW);
            printf("  ============================================\n");
            printf("  |            IT'S A DRAW!                  |\n");
            printf("  ============================================\n");
            Beep(500, 300);
        }
        else if (result == 1)
        {
            playerScore++;
            setColor(COLOR_GREEN);
            printf("  ============================================\n");
            printf("  |            YOU WIN!                      |\n");
            printf("  ============================================\n");
            Beep(800, 200);
            Beep(1000, 300);
        }
        else
        {
            computerScore++;
            setColor(COLOR_RED);
            printf("  ============================================\n");
            printf("  |            YOU LOSE!                     |\n");
            printf("  ============================================\n");
            Beep(300, 400);
        }
        setColor(COLOR_RESET);

        gamesPlayed++;

        printf("\n  Press any key to continue...");
        getch();
    }
}

