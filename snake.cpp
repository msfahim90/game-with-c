/*
 * Snake Game Implementation
 * Features:
 * - Three difficulty levels (Easy, Medium, Hard)
 * - Lives system
 * - Power-ups (Speed boost, Slow down, Score multiplier, Invincibility)
 * - Obstacles in hard mode
 * - High score system with file storage
 * - Pause functionality
 */

#include "common.h"

// Snake game constants
#define WIDTH 50
#define HEIGHT 20
#define MAX_POWERUPS 3
#define MAX_OBSTACLES 10
#define MAX_LIVES 3
#define MAX_SNAKE_LENGTH 200

// Structures
typedef struct {
    int x, y;
    int active;
    int type;
    int duration;
} PowerUp;

typedef struct {
    int x, y;
} Obstacle;

typedef struct {
    char name[50];
    int score;
} HighScore;

typedef struct {
    int x[MAX_SNAKE_LENGTH], y[MAX_SNAKE_LENGTH];
    int length;
    int dirX, dirY;
    int score;
    int lives;
    int gameOver;
    int paused;
    int difficulty;
    int speed;
    int foodX, foodY;
    int multiplier;
    int invincible;
    int multiplierTimer;
    PowerUp powerups[MAX_POWERUPS];
    Obstacle obstacles[MAX_OBSTACLES];
    int obstacleCount;
} SnakeGame;

// Function prototypes
void initializeSnake(SnakeGame *game);
void drawSnake(SnakeGame *game);
void updateSnake(SnakeGame *game);
void spawnPowerUp(SnakeGame *game);
void spawnObstacles(SnakeGame *game);
void updatePowerUps(SnakeGame *game);
void showPauseMenu(SnakeGame *game);
void saveHighScore(int score, char *name);
void displayHighScores();
int selectDifficulty();


int selectDifficulty() {
    clearScreen();
    setColor(COLOR_YELLOW);
    printf("\n=== SNAKE GAME - SELECT DIFFICULTY ===\n\n");
    setColor(COLOR_RESET);
    printf("1. Easy   - 3 lives\n");
    printf("2. Medium - 2 lives\n");
    printf("3. Hard   - 1 life, obstacles\n");
    printf("4. Back to Main Menu\n\n");
    printf("Enter choice (1-4): ");
    
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        clearInputBuffer();
        return 1;
    }
    clearInputBuffer();
    
    if (choice == 4) return -1;
    return choice - 1;
}
