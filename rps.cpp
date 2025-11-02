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

