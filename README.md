# CS211 Project - 2048 and Luhn (MW, Group 99)

This repo has my two programs for the CS211 group project. They're separate programs and each one builds on its own.

**Name:** Francisco Ibarra
**GitHub:** [2Praetorian](https://github.com/2Praetorian)
**Repo:** https://github.com/2Praetorian/CS211-project-mw-group

I did this one by myself, so I reviewed and merged my own pull requests.

## The programs

- **game2048** - 2048 on a 5x5 board in the console. Tiles slide and equal tiles merge (once per move). It keeps score, counts moves, shows the highest tile, tells you when you hit 2048, and knows when the game is over. You can save and load a game.
- **luhn** - checks if a 16 digit number passes the Luhn checksum. Passing just means the digits add up right, it doesn't mean it's a real card.

## Build and run

Run these from the top project folder (the one with this README). I used g++ in Git Bash on Windows. The same commands work on Mac/Linux.

**2048**
```
g++ -std=c++17 -Wall -Wextra -pedantic game2048/main.cpp game2048/2048_helper.cpp -o game2048_app
./game2048_app
```

**Luhn**
```
g++ -std=c++17 -Wall -Wextra -pedantic luhn/main.cpp luhn/luhn.cpp -o luhn_app
./luhn_app
```

**Tests**
```
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_2048.cpp game2048/2048_helper.cpp -o test_2048
./test_2048
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_luhn.cpp luhn/luhn.cpp -o test_luhn
./test_luhn
```

## 2048 controls

Type one letter and press Enter.

| Key | What it does |
|---|---|
| u / d / l / r | move up / down / left / right |
| s | save the game to `savegame.txt` |
| o | open (load) the game from `savegame.txt` |
| n | new game (asks y/n first) |
| h | help |
| e | exit |

- A new 2 only shows up after a move that actually changes the board.
- When you reach 2048 it says you won, and you can keep playing.
- If the board is full and nothing can merge, it's game over. You can still save, load, start a new game, see help, or exit.

## Saving and loading

- There's one save slot: `savegame.txt` in whatever folder you run the game from (the current working directory). Saving again replaces the old save.
- Loading checks the whole file first (the `CS211_2048_V1` marker, the score and move count, and exactly 25 tiles that are 0 or powers of two). If anything is missing or wrong, it shows an error and your current game doesn't change.
- `game2048/sample_save.txt` is a valid example save. To try it, copy it to `savegame.txt` in the folder you run from, then press `o`.

## Luhn

Type a 16 digit number and press Enter, or type `q` to quit. Anything that isn't exactly 16 digits (letters, spaces in the middle, dashes, wrong length) gets a format error, and you can try again.

## Known limitations

- There's only one save slot.
- The random number sequence isn't saved, so after loading, the new tiles won't be in the same spots as before.
- Commands have to be typed and followed by Enter (no arrow keys).
