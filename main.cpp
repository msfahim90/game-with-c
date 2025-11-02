#include "common.h"

// Utility function implementations
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void clearScreen()
{
    system("cls");
}

void displayMenu()
{
    clearScreen();
    setColor(COLOR_CYAN);
    printf("\n");
    printf("  ============================================\n");
    printf("  |   ULTIMATE GAME COLLECTION             |\n");
    printf("  ============================================\n");
    setColor(COLOR_RESET);
    printf("  |                                          |\n");
    printf("  |  ");
    setColor(COLOR_GREEN);
    printf("1.");
    setColor(COLOR_RESET);
    printf(" Tic Tac Toe                         |\n");
    printf("  |  ");
    setColor(COLOR_GREEN);
    printf("2.");
    setColor(COLOR_RESET);
    printf(" Snake Game                          |\n");
    printf("  |  ");
    setColor(COLOR_GREEN);
    printf("3.");
    setColor(COLOR_RESET);
    printf(" Rock Paper Scissors                 |\n");
    printf("  |  ");
    setColor(COLOR_GREEN);
    printf("4.");
    setColor(COLOR_RESET);
    printf(" Exit                                |\n");
    printf("  |                                          |\n");
    setColor(COLOR_CYAN);
    printf("  ============================================\n\n");
    setColor(COLOR_RESET);
}

int getUserChoice()
{
    int choice;
    printf("  Enter your choice (1-4): ");
    if (scanf("%d", &choice) != 1)
    {
        clearInputBuffer();
        return -1;
    }
    clearInputBuffer();
    return choice;
}

int main()
{
    int choice;
    srand((unsigned int)time(NULL));

    while (1)
    {
        displayMenu();
        choice = getUserChoice();

        switch (choice)
        {
        case 1:
            playTicTacToe();
            break;
        case 2:
            playSnakeGame();
            break;
        case 3:
            playRockPaperScissors();
            break;
        case 4:
            clearScreen();
            setColor(COLOR_CYAN);
            printf("\n\n  Thank you for playing! Goodbye!\n\n");
            setColor(COLOR_RESET);
            return 0;
        default:
            setColor(COLOR_RED);
            printf("\n\n  Invalid choice! Press any key to try again...");
            setColor(COLOR_RESET);
            getch();
        }
    }

    return 0;
}
