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
