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

int main() {

    system("color 4F");

    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP); // Background music

    srand(time(0));

    int x = 1;                     // Player position (0–2)
    int step = 0;                  // Obstacle vertical position
    int obstaclePos = rand() % 3;  // obstacle lane
    int score = 0;                 // (NEW) Score

    while (1) {

        /* INPUT */
        if (_kbhit()) {
            int ch = getch();

            // Quit game (NEW)
            if (ch == 'q' || ch == 'Q') {
                printf("\nYou Quit the Game.\n");
                break;
            }

            // Arrow keys
            if (ch == 75 && x > 0) x--;  // left
            if (ch == 77 && x < 2) x++;  // right
        }

        /* DRAW */
        clear_screen_fast();

        printf("Score: %d   (Press Q to Quit)\n", score); // (NEW HUD)

        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                // visible obstacle (simple change)
                if (obstaclePos == 0)
                    printf("| X         |\n");
                else if (obstaclePos == 1)
                    printf("|     X     |\n");
                else if (obstaclePos == 2)
                    printf("|         X |\n");

            } else {
                printf("|           |\n");
            }
        }

        /* PLAYER */
        if (x == 0)
            printf("| A         |\n");
        else if (x == 1)
            printf("|     A     |\n");
        else if (x == 2)
            printf("|         A |\n");

        /* COLLISION */
        if (step == 10 && x == obstaclePos) {

            PlaySound(NULL, NULL, 0);   // stop bg music
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC); // crash sound

            Sleep(2000);
            printf("\nGAME OVER!\n");
            break;
        }

        Sleep(120); // original speed

        /* UPDATE POSITION */
        step++;

        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3;

            score++; // (NEW) score increments
        }

        /* WIN CONDITION (NEW) */
        if (score >= 20) {
            printf("\nYOU WIN THE GAME!\n");
            break;
        }
    }

    return 0;
}
