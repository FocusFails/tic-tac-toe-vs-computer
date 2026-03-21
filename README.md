# tic-tac-toe-vs-computer
C Programming | End-of-Course Project Work

I'll be writing some documentation down below so I don't forget topics when I write project report later on:

**1. Project Overview:**
> For my end-of-course project, I built a terminal-based Tic-Tac-Toe game where a human player competes against an AI. I also wanted to explore file & structures so I implemented a persistent leaderboard system that tracks player progress across different sessions using a local leaderboard.txt file.

**2. Core Logic & Features:**
> **Main Game Loop:** 
  >> The game runs on a **while** loop that continues as long as there is no winner (**win == 'N'**) and there are empty spaces available.
  >> It handles turn-taking between the player and the AI.
  >> It evaluates the board state after every move to immediately catch a win or a draw.

> **Game AI:** 
  >> **To Win:** It simulates placing its own mark (**'O'**) in every empty square. If one of those hypothetical moves results in a win, it takes that square in the real game.
>  > 
  >> **To Block:** If it can’t win, it simulates the player's next move. If the player would win on their next turn, the computer places an **'O'** there to block them.
>  > 
  >> **Neutral:** If no immediate win or block is found, it falls back to a **rand()** generator to pick a spot.

> **Input Validation:** 
  >> I spent time making sure the game is user-friendly. If a player tries to pick a square that is already occupied or enters a number outside the 1–9 range, the program catches the error and prompts them to try again rather than just outright ending the turn.

**3. Engineering Workarounds:**
> **Simulating Multi-Value Returns using Array:** 
  >> One of the technical hurdles I faced was that C functions can typically only return a single value. However, my **check_winning_move()** function needed to provide both a row and a column index to the computer. So, I instead leveraged the way arrays are handled in memory.
>  > 
  >> By passing a small integer array **rowcol[2]** into the function, I could store the calculated coordinates directly into those memory slots. This allowed the data to persist even after the function finished executing, effectively letting me "**return**" two distinct values back to the AI logic.

> **Coordinate Mapping (1D to 2D):**
  >> To make the game intuitive, I let players choose squares 1–9. To translate this for the computer's 3x3 grid, I used mathematical mapping:
>  > 
>  > **Row = (Input - 1) / 3**
>  > 
>  > **Column = (Input - 1) % 3**
>  > 
>  > This removed the need for a large chain of conditional statements and kept the code clean.

> **Non-Destructive Simulation:**
> > When the AI "looks into the future" to test moves, it essentially places a mark on the board and calls the **checkWinner()** function to see if the move is winning or not. This modifies the board in real time.
> > 
> > To prevent the AI from accidentally making a move during the "thinking" phase, I implemented a simple strategy that makes the AI places a mark, checks for a win, and then immediately resets that exact square to empty (**' '**) before the player ever sees it. 

4. **Known Challenges & Future Improvements:** 
>**[✅] Input Bug:** If the player enters a character/string when computer is looking for an integer, the program bugs out. This is a simple fix I have left out for other group members to solve.

>**[✅] Score problem:** A player cannot have more than a score of 1 because if he wants to play the game again it asks for his name, and this score does not stack but appears on the leaderboard as two seperate entries. This will lead to the next problem which is... 

>**[✅] The Leaderboard "Append" Problem:** Currently, updatelb uses **"a"** (append mode). This creates a new entry every time a game ends.
  >> **The rough plan:** Make updatelb() read everything into a massive array, search for exact same names, then add the integers assosicated with those names, then finally rewrite that into the original file.

>**[✅] Sorting:** A leaderboard isn't very useful if the top player is buried at the bottom. I'm planning to eventually add a sorting algorithm to the leaderboard so the highest scores appear at the top automatically. 


