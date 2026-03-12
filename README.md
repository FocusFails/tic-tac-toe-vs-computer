# tic-tac-toe-vs-computer
C Programming | End-of-Course Project Work

1. Project Overview: 
> For my end-of-course project, I built a terminal-based Tic-Tac-Toe game where a human player competes against an AI. I also wanted to
  explore file I/O so I implemented a persistent leaderboard system that tracks player progress across different sessions using a local
  leaderboard.txt file.

2. Core Logic & Features:
> Core Game Loop: 
  > The game runs on a while loop that continues as long as there is no winner (win == 'N') and there are empty spaces available.
  > It handles turn-taking between the player and the AI.
  > It evaluates the board state after every move to immediately catch a win or a draw.

> Game AI: 
  > To Win: It simulates placing its own mark ('O') in every empty square. If one of those hypothetical moves results in a win, it takes       that square in the real game.
  > To Block: If it can’t win, it simulates the player's next move. If the player would win on their next turn, the computer places an        'O' there to block them.
  > Neutral: If no immediate win or block is found, it falls back to a rand() generator to pick a spot.

> Input Validation: 
  > I spent time making sure the game is user-friendly. If a player tries to pick a square that is already occupied or enters a number
    outside the 1–9 range, the program catches the error and prompts them to try again rather than just outright ending the turn.

3. Known Challenges & Future Improvements: 
> Input Bug: If the player enters a character/string when computer is looking for an integer, the program bugs out. This is a simple fix I have left out for others to solve. 

> The Leaderboard "Append" Problem: Currently, updatelb uses "a" (append mode). This creates a new entry every time a game ends.
  >> The rough plan: Make updatelb() read everything into a massive array, search for exact same names, then add the integers
    assosicated with those names, then finally rewrite that into the original file.

> Sorting: A leaderboard isn't very useful if the top player is buried at the bottom. I'm planning to eventually add a sorting algorithm
  to the leaderboard so the highest scores appear at the top automatically. 

