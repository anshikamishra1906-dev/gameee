#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

int main() {
    system("color 0A");
    srand(time(0));

    // Background music (loop)
    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);

    int player = 1;
    int step1 = 0, step2 = -6;
    int lane1 = rand() % 3;
    int lane2 = rand() % 3;

    int score = 0;
    int lives = 3;
    int level = 1;

    const int speed = 120;   // ← ORIGINAL GAME SPEED

    while (1) {

        // INPUT
        if (_kbhit()) {
            char ch = getch();
            if (ch == 75 && player > 0) player--;
            if (ch == 77 && player < 2) player++;
        }

        // DRAW
        clear_screen_fast();
        printf("+--------------+  SCORE: %d  LIVES: %d  LEVEL: %d\n",
               score, lives, level);

        for (int i = 0; i < 12; i++) {

            // obstacle 1 (X)
            if (i == step1) {
                if (lane1 == 0) printf("| X          |\n");
                else if (lane1 == 1) printf("|     X      |\n");
                else printf("|         X  |\n");

            // obstacle 2 (@)
            } else if (i == step2) {
                if (lane2 == 0) printf("| @          |\n");
                else if (lane2 == 1) printf("|     @      |\n");
                else printf("|         @  |\n");

            } else {
                printf("|             |\n");
            }
        }

        // PLAYER
        if (player == 0) printf("| A           |\n");
        if (player == 1) printf("|     A       |\n");
        if (player == 2) printf("|         A   |\n");

        // COLLISION
        if ((step1 == 12 && player == lane1) ||
            (step2 == 12 && player == lane2)) {

            lives--;

            // Play crash sound
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);

            Sleep(700);

            // Restart background music
            PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);

            if (lives <= 0) {
                printf("\nGAME OVER! FINAL SCORE = %d\n", score);
                break;
            }

            // reset obstacle 1
            step1 = 0;
            lane1 = rand() % 3;
        }

        // SCORING
        if (step1 == 12) score++;
        if (step2 == 12) score++;

        // LEVEL (does NOT change speed)
        if (score % 10 == 0 && score != 0) {
            level++;
        }

        Sleep(speed);

        // MOVE OBSTACLES
        step1++;
        step2++;

        if (step1 > 12) {
            step1 = 0;
            lane1 = rand() % 3;
        }

        if (step2 > 12) {
            step2 = -6;
            lane2 = rand() % 3;
        }
    }

    PlaySound(NULL, NULL, 0);
    return 0;
}
