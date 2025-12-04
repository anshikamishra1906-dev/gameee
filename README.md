## ANALYSIS

The program is a small console-based lane game where:

A player character sits at the bottom of the screen

An obstacle drops from the top in one of three lanes

The player can move left or right using arrow keys

If the obstacle reaches the bottom in the same lane as the player, the game ends

Background music plays in a loop while the game runs

A crash sound plays when the player gets hit

Even though the idea is simple, the code demonstrates several important concepts in C programming and basic game logic.

 1. Purpose of the Included Libraries

The code begins by including several Windows-specific libraries:

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>


Each one serves a different purpose:

stdio.h → printing text and formatting

conio.h → detecting keyboard input instantly without waiting for Enter

windows.h → cursor control, colors, sleep function

stdlib.h & time.h → generating random obstacle positions

mmsystem.h → sound playback (background and crash audio)

This combination allows the game to function like a real-time console game with sound.

 2. Flicker-Free Screen Refresh

The code uses a custom function instead of system("cls") to avoid flickering:

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}


This moves the console cursor back to the top-left corner, letting the program redraw the screen smoothly.
It imitates a “frame refresh,” which is important in simple animation.

 3. Initial Game Setup

The code sets console colors, plays looping background music, and seeds the random number generator:

system("color 4F");
PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
srand(time(0));


Here’s what this does:

Red background + bright text

Continuous background music

Random obstacle lanes for each run

 4. Important Game Variables

The program uses a few simple integer variables:

int x = 1;             // player lane: 0, 1, or 2
int step = 0;          // how far down the obstacle has fallen
int obstaclePos = rand() % 3;  // starting lane of obstacle


Explanation:

The player begins in the middle lane (1)

The obstacle starts at the top

rand() % 3 ensures the obstacle is in one of three lanes

These variables define the core gameplay behavior.

 5. Game Loop (Runs Until Game Over)

The entire game runs inside:

while (1) { ... }


Inside this loop, the game repeatedly:

Reads input

Draws the current frame

Updates obstacle movement

Checks for collisions

Waits a short time

Repeats

This creates the animation experience.

 6. Handling Arrow Key Input

The game uses _kbhit() and getch() to detect arrow keys instantly:

if (_kbhit()) {
    char ch = getch();
    if (ch == 75 && x > 0) x--;
    if (ch == 77 && x < 2) x++;
}


75 = left arrow

77 = right arrow

The checks ensure the player cannot move outside the 3-lane boundary.

 7. Drawing the Game on the Screen

The game starts by clearing the previous frame and printing lane boundaries:

clear_screen_fast();
printf("|--- --- ---|\n");


Then it prints 10 rows that act as the falling path.

At the row where step equals i, it prints the obstacle in the correct lane.
Other rows print empty spaces.

Example logic:

If obstacle is in lane 0 → | X |

If lane 1 → | X |

If lane 2 → | X|

Finally, the player is drawn at the bottom row in whichever lane x indicates.

 8. Collision Detection Logic

Collision happens only if both conditions are true:

if (step == 10 && x == obstaclePos) {


This means:

The obstacle has reached the bottom row

The player is in the same lane

If that happens:

Background music stops

Crash sound plays

A “GAME OVER” message appears

The loop ends

 9. Updating Obstacle Position

Each frame, the obstacle moves down by 1:

step++;


When it passes beyond the bottom (step > 10):

step = 0;
obstaclePos = rand() % 3; // new lane


This creates a repeating flow of falling obstacles.

 10. Game Speed

A small sleep delay controls the game speed:

Sleep(120);


This keeps the movement smooth and consistent.
Changing this value would directly change how fast the game feels.

 My Final Summary

This original code is a good example of a simple console game implemented with basic C concepts and Windows-specific functions.
Even though the game is small, it demonstrates:

Real-time user input

Fast screen refreshing

Randomized gameplay

Collision detection

Sound effects and looping background music

Animation using a loop and timed delays

It’s a straightforward, beginner-friendly design that works well for understanding how basic game logic functions in a console environment.



## Documentation of All Modifications 

Below is a clear explanation of all the changes made to the original lane-game program. I’ve written it in a simple, human-like way so that anyone can understand what was modified and why.

1. Added a Score System

What was added:
A basic score counter that increases every time an obstacle reaches the bottom without hitting the player.

Why it was added:
It gives the player a sense of progress and makes the game feel more rewarding.

How it works:
Each time an obstacle resets at the bottom, the score increases by 1.
The score is shown on-screen during gameplay.

2. Added Player Lives (3 chances)

What was added:
A simple life system where the player starts with 3 lives.

Why it was added:
Instead of losing immediately on the first crash, the player now gets a few chances, making the game more enjoyable and less punishing.

How it works:
A variable named lives begins at 3.
Every time the player hits an obstacle, the lives go down by 1.
When lives reach 0, the game ends.

3. Added a Start Menu

What was added:
A simple menu that appears before the game starts:

1. Start Game
2. Quit


Why it was added:
It makes the game feel more complete and lets the user choose when to begin.

How it works:
A small loop displays the options.
Pressing 1 starts the game, while pressing 2 exits.

4. Added Game Restart Option

What was added:
After the game ends, the program asks the player:

Play again? (y/n)


Why it was added:
This allows players to restart without closing and re-running the program.

How it works:
Pressing y starts the game again, while n exits the program.

5. Added Multiple Obstacles (Two Falling Objects)

What was added:
Two falling obstacles instead of just one.

Why it was added:
It increases the challenge slightly while still keeping the code easy to understand.

How it works:
Two different variables control two independent obstacles.
If either obstacle hits the player, they lose a life.
If both pass safely, the score increases twice.

No arrays, no complex logic—just two separate obstacle systems kept simple.

Summary of Features Added (Four Beginner-Friendly Additions)

Score system

Player lives

Start menu

Restart option

Multiple obstacles (extra simple implementation)

No advanced features like difficulty scaling, file handling, or shooting actions were added, to keep the game beginner-friendly.
