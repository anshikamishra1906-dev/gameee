Documentation of All Modifications 

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
