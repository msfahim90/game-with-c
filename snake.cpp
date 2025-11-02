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


void playSnakeGame() {
    int difficulty = selectDifficulty();
    
    if (difficulty == -1) return;
    
    char playAgain;
    do {
        SnakeGame game;
        char input;
        
        game.difficulty = difficulty;
        initializeSnake(&game);
        
        clearScreen();
        hideCursor();
        setColor(COLOR_YELLOW);
        printf("\n=== SNAKE GAME ===\n");
        setColor(COLOR_RESET);
        printf("Controls: W=Up S=Down A=Left D=Right | P=Pause Q=Quit\n");
        printf("Lives: %d | Difficulty: %s\n", game.lives, 
               game.difficulty == 0 ? "Easy" : game.difficulty == 1 ? "Medium" : "Hard");
        
        drawSnake(&game);
        
        printf("\n\nPress any key to start...");
        getch();
        
        while (!game.gameOver) {
            if (_kbhit()) {
                input = getch();
                input = tolower(input);
                
                if (input == 'q') {
                    game.gameOver = 1;
                    break;
                }
                if (input == 'p') {
                    game.paused = !game.paused;
                    if (game.paused) showPauseMenu(&game);
                }
                
                if (!game.paused) {
                    if (input == 'w' && game.dirY != 1) { game.dirX = 0; game.dirY = -1; }
                    else if (input == 's' && game.dirY != -1) { game.dirX = 0; game.dirY = 1; }
                    else if (input == 'a' && game.dirX != 1) { game.dirX = -1; game.dirY = 0; }
                    else if (input == 'd' && game.dirX != -1) { game.dirX = 1; game.dirY = 0; }
                }
            }
            
            if (!game.paused) {
                updateSnake(&game);
                drawSnake(&game);
                Sleep(game.speed);
            }
        }
        
        clearScreen();
        setColor(COLOR_RED);
        printf("\n\n==================================\n");
        printf("  |        GAME OVER!              |\n");
        printf("  |                                |\n");
        printf("  |    Final Score: %-3d           |\n", game.score);
        printf("  ==================================\n\n");
        setColor(COLOR_RESET);
        
        printf("Enter your name: ");
        char name[50];
        
        clearInputBuffer();
        
        if (fgets(name, sizeof(name), stdin) != NULL) {
            name[strcspn(name, "\n")] = 0;
            if (strlen(name) > 0) {
                saveHighScore(game.score, name);
            }
        }
        
        printf("\n");
        setColor(COLOR_YELLOW);
        printf("Play again? (Y/N): ");
        setColor(COLOR_RESET);
        
        char response[10];
        if (scanf("%s", response) == 1) {
            playAgain = tolower(response[0]);
        } else {
            playAgain = 'n';
        }
        clearInputBuffer();
        
    } while (playAgain == 'y');
}


void initializeSnake(SnakeGame *game) {
    game->length = 3;
    game->x[0] = WIDTH / 2;
    game->y[0] = HEIGHT / 2;
    
    for (int i = 1; i < game->length; i++) {
        game->x[i] = game->x[0] - i;
        game->y[i] = game->y[0];
    }
    
    game->dirX = 1;
    game->dirY = 0;
    game->foodX = rand() % (WIDTH - 2) + 1;
    game->foodY = rand() % (HEIGHT - 2) + 1;
    game->score = 0;
    game->gameOver = 0;
    game->paused = 0;
    game->multiplier = 1;
    game->invincible = 0;
    game->multiplierTimer = 0;
    
    game->lives = game->difficulty == 0 ? 3 : game->difficulty == 1 ? 2 : 1;
    game->speed = game->difficulty == 0 ? 150 : game->difficulty == 1 ? 100 : 70;
    
    for (int i = 0; i < MAX_POWERUPS; i++) {
        game->powerups[i].active = 0;
    }
    
    game->obstacleCount = 0;
    if (game->difficulty == 2) {
        spawnObstacles(game);
    }
    
    if (rand() % 3 == 0) spawnPowerUp(game);
}


void spawnPowerUp(SnakeGame *game) {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (!game->powerups[i].active) {
            int validPosition = 0;
            int attempts = 0;
            
            while (!validPosition && attempts < 50) {
                game->powerups[i].x = rand() % (WIDTH - 2) + 1;
                game->powerups[i].y = rand() % (HEIGHT - 2) + 1;
                
                validPosition = 1;
                if (game->powerups[i].x == game->foodX && game->powerups[i].y == game->foodY) {
                    validPosition = 0;
                }
                
                for (int j = 0; j < game->length; j++) {
                    if (game->powerups[i].x == game->x[j] && game->powerups[i].y == game->y[j]) {
                        validPosition = 0;
                        break;
                    }
                }
                
                attempts++;
            }
            
            if (validPosition) {
                game->powerups[i].type = rand() % 4;
                game->powerups[i].active = 1;
                game->powerups[i].duration = 50;
            }
            break;
        }
    }
}



