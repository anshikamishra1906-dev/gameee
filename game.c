#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

/* Clear screen without flicker */
void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

/* GAME LOOP */
int playGame() {

    int x = 1;                        // Player position
    int lives = 3;                    // Lives
    int score = 0;                    // Score

    int step1 = 0;                    // Obstacle 1 vertical
    int step2 = -5;                   // Obstacle 2 starts higher
    int lane1 = rand() % 3;           // Obstacle 1 lane
    int lane2 = rand() % 3;           // Obstacle 2 lane

    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP); // background music

    while (1) {

        /* INPUT */
        if (_kbhit()) {
            int ch = getch();

            if (ch == 'q' || ch == 'Q') {
                printf("\nYou Quit the Game.\n");
                return 0;
            }

            if (ch == 75 && x > 0) x--; // left
            if (ch == 77 && x < 2) x++; // right
        }

        /* DRAW EVERYTHING */
        clear_screen_fast();
        printf("Lives: %d   Score: %d   (Press Q to Quit)\n", lives, score);
        printf("|--- --- ---|\n");

        for (int row = 0; row < 10; row++) {

            // Row has BOTH obstacles considered
            if (row == step1 && row == step2 && lane1 == lane2) {
                // If they randomly overlap in same lane
                if (lane1 == 0)  printf("| XX        |\n");
                if (lane1 == 1)  printf("|    XX     |\n");
                if (lane1 == 2)  printf("|        XX |\n");
            }

            else if (row == step1) {
                if (lane1 == 0)  printf("| X         |\n");
                if (lane1 == 1)  printf("|     X     |\n");
                if (lane1 == 2)  printf("|         X |\n");
            }

            else if (row == step2) {
                if (lane2 == 0)  printf("| X         |\n");
                if (lane2 == 1)  printf("|     X     |\n");
                if (lane2 == 2)  printf("|         X |\n");
            }

            else printf("|           |\n");
        }

        /* DRAW PLAYER */
        if (x == 0)  printf("| A         |\n");
        if (x == 1)  printf("|     A     |\n");
        if (x == 2)  printf("|         A |\n");

        /* COLLISION CHECK WITH OBSTACLE 1 */
        if (step1 == 10 && x == lane1) {

            PlaySound(NULL, NULL, 0);
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);
            Sleep(800);

            lives--;

            if (lives <= 0) {
                printf("\nGAME OVER!\n");
                return 0;
            }

            step1 = 0;
            lane1 = rand() % 3;
        }

        /* COLLISION CHECK WITH OBSTACLE 2 */
        if (step2 == 10 && x == lane2) {

            PlaySound(NULL, NULL, 0);
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);
            Sleep(800);

            lives--;

            if (lives <= 0) {
                printf("\nGAME OVER!\n");
                return 0;
            }

            step2 = 0;
            lane2 = rand() % 3;
        }

        Sleep(120); // same speed

        /* UPDATE MOVEMENT */
        step1++;
        step2++;

        /* RESET OBSTACLES WHEN THEY PASS BOTTOM */
        if (step1 > 10) { 
            step1 = 0; 
            lane1 = rand() % 3;
            score++;
        }

        if (step2 > 10) { 
            step2 = 0; 
            lane2 = rand() % 3;
            score++;
        }
    }
}

/********* MAIN MENU + RESTART OPTION *********/

int main() {

    srand(time(0));

    while (1) {

        int choice;

        printf("\n===== LANE GAME =====\n");
        printf("1. Start Game\n");
        printf("2. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 2) {
            printf("Goodbye!\n");
            break;
        }

        if (choice != 1) {
            printf("Invalid option!\n");
            continue;
        }

        system("cls");
        playGame();

        char again;
        printf("\nPlay again? (y/n): ");
        scanf(" %c", &again);

        if (again == 'n' || again == 'N') {
            printf("Thanks for playing!\n");
            break;
        }

        system("cls");
    }

    return 0;
}
