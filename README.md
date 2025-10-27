# tictac
1. Regular Tic Tac Toe

Classic mode — two players take turns placing X and O on a 3×3 grid until one achieves three in a row.

2. Battle Tic Tac Toe

A fantasy-enhanced version of Tic Tac Toe where each player chooses an archetype:

⚗️ The Alchemist

Can swap two existing marks on the board instead of placing a new one.

Rules:

Both positions must already contain marks.

Cannot swap identical marks.

Cannot perform both a move and a swap in the same turn.

🛡️ The Paladin

Can shift any mark (yours or your opponent’s) to an adjacent empty square.

Rules:

Only adjacent squares are valid.

Cannot move a mark to an occupied space.

Must choose valid positions (1–9).

Cannot perform both a move and a shift in the same turn.

🧩 Controls

Enter y or n when prompted to start or replay the game.

Choose 1 or 2 to select your preferred mode.

For each turn:

Choose between a regular move or a special ability.

Input positions as numbers 1–9, corresponding to board spaces.

Example board layout:

 1 | 2 | 3
-----------
 4 | 5 | 6
-----------
 7 | 8 | 9

🧠 How It Works

The game board is represented as a vector<string> with ASCII formatting.

Input validation ensures only legal moves are made.

Battle Mode adds interactive ability prompts and logical checks for archetype powers.

The board resets automatically if players choose to play again.
