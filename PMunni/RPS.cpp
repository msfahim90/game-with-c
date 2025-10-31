#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    printf("\nPress any key to continue...");
    _getch();
}

void rockPaperScissors() {
    int mode, p1, p2, computer;
    char again;

    do {
        clearScreen();
        printf("\n\n  ====================================\n");
        printf("         ROCK - PAPER - SCISSORS\n");
        printf("  ====================================\n\n");
        printf("  1. Player vs Computer\n");
        printf("  2. Player vs Player\n");
        printf("  ====================================\n");
        printf("  Enter mode (1-2): ");

        if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
            while (getchar() != '\n');
            printf("\n  Invalid input!");
            pauseScreen();
            continue;
        }
        while (getchar() != '\n');

        if (mode == 1) {
            srand(time(NULL));
            clearScreen();
            printf("\nChoose your option:\n");
            printf("1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter choice (1-3): ");
            scanf("%d", &p1);
            while (getchar() != '\n');

            if (p1 < 1 || p1 > 3) {
                printf("Invalid choice!");
                pauseScreen();
                continue;
            }

            computer = rand() % 3 + 1;

            clearScreen();
            printf("\nYou chose: %s\n", (p1 == 1) ? "Rock" : (p1 == 2) ? "Paper" : "Scissors");
            printf("Computer chose: %s\n", (computer == 1) ? "Rock" : (computer == 2) ? "Paper" : "Scissors");

            if (p1 == computer)
                printf("\nResult: It's a Draw!\n");
            else if ((p1 == 1 && computer == 3) || (p1 == 2 && computer == 1) || (p1 == 3 && computer == 2))
                printf("\nResult: You Win!\n");
            else
                printf("\nResult: Computer Wins!\n");

        } else if (mode == 2) {
            clearScreen();
            printf("\nPlayer 1, choose your option:\n");
            printf("1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter choice (1-3): ");
            scanf("%d", &p1);
            while (getchar() != '\n');

            clearScreen();
            printf("\nPlayer 2, choose your option:\n");
            printf("1. Rock\n2. Paper\n3. Scissors\n");
            printf("Enter choice (1-3): ");
            scanf("%d", &p2);
            while (getchar() != '\n');

            clearScreen();
            printf("Player 1 chose: %s\n", (p1 == 1) ? "Rock" : (p1 == 2) ? "Paper" : "Scissors");
            printf("Player 2 chose: %s\n", (p2 == 1) ? "Rock" : (p2 == 2) ? "Paper" : "Scissors");

            if (p1 == p2)
                printf("\nResult: It's a Draw!\n");
            else if ((p1 == 1 && p2 == 3) || (p1 == 2 && p2 == 1) || (p1 == 3 && p2 == 2))
                printf("\nResult: Player 1 Wins!\n");
            else
                printf("\nResult: Player 2 Wins!\n");
        }

        printf("\n====================================\n");
        printf("Play again? (Y/N): ");
        again = _getch();

    } while (again == 'y' || again == 'Y');

    printf("\n\nReturning to menu...\n");
    Sleep(1000);
}

int main() {
    rockPaperScissors();
    return 0;
}
