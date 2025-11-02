#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Color codes
#define COLOR_RESET 7
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_MAGENTA 13

// Common utility functions
void setColor(int color);
void hideCursor();
void clearScreen();
void clearInputBuffer();

// Game function prototypes
void playTicTacToe();
void playSnakeGame();
void playRockPaperScissors();

#endif
