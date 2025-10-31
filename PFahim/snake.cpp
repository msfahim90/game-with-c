/*
 snake_dev2.c
 Standalone Snake Game for Developer 2
 Compile (Windows/MinGW): gcc snake_dev2.c -o snake_dev2.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    // _getch(), _kbhit()
#include <time.h>
#include <windows.h>  // Sleep(), COORD, SetConsoleCursorPosition

#define WIDTH 40
#define HEIGHT 20
#define MAX_LENGTH 100
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

/* Game state */
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int snakeLength, foodX, foodY, direction, score, gameOver, difficulty, lives;
int highScore = 0, isPaused = 0, powerUpX, powerUpY, powerUpActive = 0;
int powerUpType = 0, multiplier = 1, multiplierTimer = 0;
int totalGames = 0, totalScore = 0;
int obstacleX[10], obstacleY[10], obstacleCount = 0;

/* Prototypes */
void snakeGame(void);
void setupSnake(void);
void drawSnake(void);
void inputSnake(void);
void logicSnake(void);
void generateFood(void);
void generatePowerUp(void);
void generateObstacles(void);
void gotoxy(int x, int y);
void hideCursor(void);
void showCursor(void);
void saveHighScore(void);
void loadHighScore(void);
void displayStats(void);

/* --- Console helpers --- */
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}

void showCursor() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(h, &info);
}

/* --- Persistence --- */
void saveHighScore() {
    FILE *f = fopen("highscore.txt", "w");
    if (f) {
        fprintf(f, "%d\n%d\n%d\n", highScore, totalGames, totalScore);
        fclose(f);
    }
}

void loadHighScore() {
    FILE *f = fopen("highscore.txt", "r");
    if (f) {
        fscanf(f, "%d %d %d", &highScore, &totalGames, &totalScore);
        fclose(f);
    }
}

/* Stats viewer (optional) */
void displayStats() {
    system("cls");
    printf("\n\n  ================================\n");
    printf("       SNAKE GAME STATISTICS\n");
    printf("  ================================\n\n");
    printf("  High Score:       %d\n", highScore);
    printf("  Total Games:      %d\n", totalGames);
    printf("  Total Score:      %d\n", totalScore);
    if (totalGames > 0)
        printf("  Average Score:    %d\n", totalScore / totalGames);
    printf("\n  ================================\n");
    printf("\n  Press any key to return...\n");
    _getch();
}

/* --- Snake game implementation --- */
void snakeGame() {
    char again;
    loadHighScore();

    system("cls");
    printf("\n\n  ====================================\n");
    printf("     SNAKE GAME - DIFFICULTY\n");
    printf("  ====================================\n\n");
    printf("  1. Easy   (Slow, 5 lives)\n");
    printf("  2. Medium (Normal, 3 lives)\n");
    printf("  3. Hard   (Fast, 1 life)\n\n");
    printf("  ====================================\n");
    printf("\n  Select (1-3): ");

    if (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
        while (getchar() != '\n');
        difficulty = 2;
    }
    while (getchar() != '\n');

    hideCursor();

    do {
        setupSnake();
        system("cls");

        while (!gameOver && lives > 0) {
            if (!isPaused) {
                drawSnake();
                inputSnake();
                logicSnake();
                int spd = (difficulty == 1) ? 150 : (difficulty == 2) ? 100 : 70;
                Sleep(spd);
            } else {
                gotoxy(WIDTH/2 - 5, HEIGHT/2);
                printf("*** PAUSED ***");
                gotoxy(WIDTH/2 - 10, HEIGHT/2 + 1);
                printf("Press P to resume");
                inputSnake();
                Sleep(100);
            }
        }

        totalGames++;
        totalScore += score;
        if (score > highScore) highScore = score;
        saveHighScore();

        showCursor();
        system("cls");
        printf("\n\n  ============================\n");
        printf("       GAME OVER!\n");
        printf("  ============================\n");
        printf("     Final Score: %d\n", score);
        printf("     High Score:  %d\n", highScore);
        printf("  ============================\n\n");
        printf("  Play again? (Y/N): ");

        again = _getch();

        if (again != 'y' && again != 'Y') {
            system("cls");
            printf("\n\n  ============================\n");
            printf("     Returning to menu...\n");
            printf("  ============================\n\n");
            Sleep(800);
        } else {
            hideCursor(); // prepare for next loop
        }

    } while (again == 'y' || again == 'Y');

    showCursor();
}

/* initialize new snake round */
void setupSnake() {
    gameOver = 0;
    isPaused = 0;
    direction = RIGHT;
    snakeLength = 3;
    score = 0;
    multiplier = 1;
    multiplierTimer = 0;
    powerUpActive = 0;

    lives = (difficulty == 1) ? 5 : (difficulty == 2) ? 3 : 1;

    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    snakeX[1] = WIDTH / 2 - 1;
    snakeY[1] = HEIGHT / 2;
    snakeX[2] = WIDTH / 2 - 2;
    snakeY[2] = HEIGHT / 2;

    srand((unsigned)time(NULL));
    generateFood();
    generateObstacles();

    if (rand() % 5 == 0) generatePowerUp();
}

/* Obstacles based on difficulty */
void generateObstacles() {
    obstacleCount = (difficulty == 3) ? 5 : (difficulty == 2) ? 3 : 0;

    for (int i = 0; i < obstacleCount; i++) {
        int valid = 0;
        while (!valid) {
            obstacleX[i] = rand() % (WIDTH - 4) + 2;
            obstacleY[i] = rand() % (HEIGHT - 4) + 2;
            valid = 1;
            if (abs(obstacleX[i] - snakeX[0]) < 5 && abs(obstacleY[i] - snakeY[0]) < 5)
                valid = 0;
        }
    }
}

/* Power-up generation */
void generatePowerUp() {
    powerUpType = rand() % 3 + 1; /* 1:S (speed?), 2:L (life?), 3:M (multiplier) */
    int valid = 0;

    while (!valid) {
        powerUpX = rand() % (WIDTH - 2) + 1;
        powerUpY = rand() % (HEIGHT - 2) + 1;
        valid = 1;
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == powerUpX && snakeY[i] == powerUpY) {
                valid = 0;
                break;
            }
        }
        for (int i = 0; i < obstacleCount; i++) {
            if (obstacleX[i] == powerUpX && obstacleY[i] == powerUpY) {
                valid = 0;
                break;
            }
        }
        if (foodX == powerUpX && foodY == powerUpY) valid = 0;
    }
    powerUpActive = 1;
}

/* Food generation ensures not on snake or obstacle */
void generateFood() {
    int valid = 0;
    while (!valid) {
        foodX = rand() % (WIDTH - 2) + 1;
        foodY = rand() % (HEIGHT - 2) + 1;
        valid = 1;

        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == foodX && snakeY[i] == foodY) {
                valid = 0;
                break;
            }
        }
        for (int i = 0; i < obstacleCount; i++) {
            if (obstacleX[i] == foodX && obstacleY[i] == foodY) {
                valid = 0;
                break;
            }
        }
    }
}

/* Draw the whole game area */
void drawSnake() {
    gotoxy(0, 0);

    for (int i = 0; i < WIDTH; i++) printf("#");
    printf("\n");

    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) {
                printf("#");
            } else {
                int drawn = 0;

                if (snakeX[0] == j && snakeY[0] == i) {
                    printf("O"); drawn = 1;
                } else {
                    for (int k = 1; k < snakeLength; k++) {
                        if (snakeX[k] == j && snakeY[k] == i) {
                            printf("o");
                            drawn = 1;
                            break;
                        }
                    }
                }

                if (!drawn && foodX == j && foodY == i) {
                    printf("*"); drawn = 1;
                }

                if (!drawn && powerUpActive && powerUpX == j && powerUpY == i) {
                    /* S, L, M icons */
                    if (powerUpType == 1) printf("S");
                    else if (powerUpType == 2) printf("L");
                    else printf("M");
                    drawn = 1;
                }

                if (!drawn) {
                    for (int k = 0; k < obstacleCount; k++) {
                        if (obstacleX[k] == j && obstacleY[k] == i) {
                            printf("X"); drawn = 1; break;
                        }
                    }
                }

                if (!drawn) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++) printf("#");
    printf("\n");

    printf("Score: %d | Lives: %d | High: %d", score, lives, highScore);
    if (multiplier > 1) printf(" | x%d", multiplier);
    printf("     \n");
    printf("Arrows: Move | P: Pause | X: Exit     \n");
}

/* Handle keyboard input (arrow keys, P, X) */
void inputSnake() {
    if (_kbhit()) {
        char k = _getch();
        if (k == -32 || k == 0) { /* arrow key prefix on Windows */
            k = _getch();
            if (!isPaused) {
                if (k == 72 && direction != DOWN) direction = UP;
                else if (k == 80 && direction != UP) direction = DOWN;
                else if (k == 75 && direction != RIGHT) direction = LEFT;
                else if (k == 77 && direction != LEFT) direction = RIGHT;
            }
        } else if (k == 'p' || k == 'P') {
            isPaused = !isPaused;
        } else if (k == 'x' || k == 'X') {
            gameOver = 1;
        }
    }
}

/* Game logic: movement, collisions, eating food/powerups */
void logicSnake() {
    /* move body */
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    /* move head */
    if (direction == UP) snakeY[0]--;
    else if (direction == DOWN) snakeY[0]++;
    else if (direction == LEFT) snakeX[0]--;
    else if (direction == RIGHT) snakeX[0]++;

    /* wall collisions */
    if (snakeX[0] <= 0 || snakeX[0] >= WIDTH - 1 ||
        snakeY[0] <= 0 || snakeY[0] >= HEIGHT - 1) {
        lives--;
        if (lives > 0) {
            /* reset head to center */
            snakeX[0] = WIDTH / 2;
            snakeY[0] = HEIGHT / 2;
            direction = RIGHT;
            Sleep(500);
        } else {
            gameOver = 1;
        }
    }

    /* self collision */
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            lives--;
            if (lives > 0) {
                snakeX[0] = WIDTH / 2;
                snakeY[0] = HEIGHT / 2;
                direction = RIGHT;
                Sleep(500);
            } else {
                gameOver = 1;
            }
        }
    }

    /* obstacle collision */
    for (int i = 0; i < obstacleCount; i++) {
        if (snakeX[0] == obstacleX[i] && snakeY[0] == obstacleY[i]) {
            lives--;
            if (lives > 0) {
                snakeX[0] = WIDTH / 2;
                snakeY[0] = HEIGHT / 2;
                direction = RIGHT;
                Sleep(500);
            } else {
                gameOver = 1;
            }
        }
    }

    /* eat food */
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        score += 10 * multiplier;
        if (snakeLength < MAX_LENGTH) snakeLength++;
        generateFood();
        if (rand() % 3 == 0 && !powerUpActive) generatePowerUp();
    }

    /* power-up pick */
    if (powerUpActive && snakeX[0] == powerUpX && snakeY[0] == powerUpY) {
        powerUpActive = 0;
        if (powerUpType == 3) {
            multiplier = 2;
            multiplierTimer = 50;
        } else if (powerUpType == 2) {
            /* give extra life if not at some arbitrary cap */
            lives++;
        } else if (powerUpType == 1) {
            /* speed boost: reduce multiplierTimer to simulate temporary advantage (kept simple) */
            if (multiplier == 1) { multiplier = 2; multiplierTimer = 30; }
        }
    }

    /* multiplier timer */
    if (multiplierTimer > 0) {
        multiplierTimer--;
        if (multiplierTimer == 0) multiplier = 1;
    }
}

/* --- main --- */
int main(void) {
    /* Provide a small menu to start or view stats */
    while (1) {
        system("cls");
        printf("\n\n  ====================================\n");
        printf("            SNAKE - DEV 2\n");
        printf("  ====================================\n\n");
        printf("  1. Play Snake\n");
        printf("  2. View Statistics\n");
        printf("  3. Exit\n\n");
        printf("  Select (1-3): ");

        int ch = 0;
        if (scanf("%d", &ch) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (ch == 1) {
            snakeGame();
        } else if (ch == 2) {
            loadHighScore();
            displayStats();
        } else if (ch == 3) {
            printf("\n  Exiting...\n");
            break;
        }
    }

    return 0;
}
