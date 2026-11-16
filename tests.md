# Test Record

All automated tests are in `tests/`. Build and run them from the top project folder:

```
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_2048.cpp game2048/2048_helper.cpp -o test_2048
./test_2048
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_luhn.cpp luhn/luhn.cpp -o test_luhn
./test_luhn
```

Movement results below are the board **right after the move and before the random 2 is added**. The random 2 is added separately in `main` only when the move changed the board.

## Part A - 2048

### 1. Sliding and merging in all four directions (including gaps)

| Direction | Start | Expected | Actual | Result |
|---|---|---|---|---|
| Left | 0 2 0 2 0 | 4 0 0 0 0, +4 | 4 0 0 0 0, +4 | Pass |
| Left | 2 2 2 0 0 | 4 2 0 0 0, +4 | 4 2 0 0 0, +4 | Pass |
| Left | 2 2 2 2 2 | 4 4 2 0 0, +8 | 4 4 2 0 0, +8 | Pass |
| Left | 2 2 4 0 0 | 4 4 0 0 0, +4 | 4 4 0 0 0, +4 | Pass |
| Left | 4 4 8 8 0 | 8 16 0 0 0, +24 | 8 16 0 0 0, +24 | Pass |
| Left | 2 4 8 0 0 | 2 4 8 0 0, +0, no change | 2 4 8 0 0, +0, no change | Pass |
| Right | 2 2 2 0 0 | 0 0 0 2 4, +4 | 0 0 0 2 4, +4 | Pass |
| Right | 0 2 0 2 0 | 0 0 0 0 4, +4 | 0 0 0 0 4, +4 | Pass |
| Up (column, top to bottom) | 2 2 2 0 0 | 4 2 0 0 0, +4 | 4 2 0 0 0, +4 | Pass |
| Down (column, top to bottom) | 2 2 2 0 0 | 0 0 0 2 4, +4 | 0 0 0 2 4, +4 | Pass |
| Down (column, top to bottom) | 0 4 0 4 8 | 0 0 0 8 8, +8 | 0 0 0 8 8, +8 | Pass |

### 2. Three and four equal tiles (no tile merges twice)

| Start | Expected | Actual | Result |
|---|---|---|---|
| Left 2 2 2 0 0 (three equal) | 4 2 0 0 0 | 4 2 0 0 0 | Pass |
| Left 2 2 2 2 0 (four equal) | 4 4 0 0 0, +8 | 4 4 0 0 0, +8 | Pass |
| Up column 2 2 2 2 0 (four equal) | 4 4 0 0 0, +8 | 4 4 0 0 0, +8 | Pass |

### 3. Slide with no merge

| Start | Expected | Actual | Result |
|---|---|---|---|
| Left 0 0 0 0 2 | 2 0 0 0 0, board changed, +0. In the game: one new 2 appears, Moves +1, Score unchanged | Same (test program + played in game) | Pass |

### 4. Unchanged move

| Start | Expected | Actual | Result |
|---|---|---|---|
| Left 2 4 8 16 32 | No change, +0. In the game: "Nothing moved", no new tile, Score and Moves unchanged | Same | Pass |

### 5. Full boards

| Board | Expected | Actual | Result |
|---|---|---|---|
| Full checkerboard of 2/4 with the last two cells 4 4 | can_move = true (a merge is possible) | true | Pass |
| Full checkerboard of 2/4 with no equal neighbors | can_move = false, no direction changes the board, game prints GAME OVER and blocks u/d/l/r | Same | Pass |

### 6. Several merges, score, reaching 2048

| Start rows | Expected | Actual | Result |
|---|---|---|---|
| 4 4 8 8 0 / 2 2 0 0 0 / 1024 1024 0 0 0, move left | 8 16 / 4 / 2048, +2076, highest tile 2048, game prints "You reached 2048!" and keeps going | Same | Pass |

### Random insertion and new game

| Test | Expected | Actual | Result |
|---|---|---|---|
| insert_random on a board with one 2 | Exactly one new tile, and it is a 2 | Same | Pass |
| new_game | Two 2s in different cells, Score 0, Moves 0 | Same | Pass |

### 7. Save, change, load

| Steps | Expected | Actual | Result |
|---|---|---|---|
| Save a board (score 8, moves 3), move left, set score 500/moves 77, load | Exact board restored, score 8, moves 3, no tile inserted, move not counted | Same | Pass |
| Load `game2048/sample_save.txt` | Loads, score 8, moves 3 | Same | Pass |

### 8. Bad save files (active game must stay the same)

| Save file problem | Expected message | Game unchanged? | Result |
|---|---|---|---|
| File missing | A load-failed message (on Windows it says "Not a valid save file") | Yes | Pass |
| Wrong marker (CS211_2048_V2) | Not a valid save file | Yes | Pass |
| Empty file | Not a valid save file | Yes | Pass |
| Only 24 tiles | Save file is incomplete | Yes | Pass |
| Tile 3 | Not 0 or a power of two | Yes | Pass |
| Tile 1 | Not 0 or a power of two | Yes | Pass |
| Tile "2x" | Not a whole number | Yes | Pass |
| Negative score | Score is ... negative | Yes | Pass |
| Score 99999999999 (too big for int) | Score is ... not a whole number | Yes | Pass |
| Extra text after the 25 tiles | Save file has extra data | Yes | Pass |

### 9. Controls (played by hand)

| Input | Expected | Actual | Result |
|---|---|---|---|
| h | Help printed, board/score/moves unchanged | Same | Pass |
| x | "Invalid command", nothing changes, no tile added | Same | Pass |
| lr (more than one letter) | "Invalid command", nothing changes | Same | Pass |
| n then no | "New game cancelled", game unchanged | Same | Pass |
| n then y | New board with two 2s, Score 0, Moves 0 | Same | Pass |
| s | "Game saved", game unchanged | Same | Pass |
| e | "Goodbye!", program ends, no tile added | Same | Pass |
| End of input (Ctrl+Z then Enter on Windows) | "End of input. Goodbye!", program ends cleanly | Same | Pass |

## Part B - Luhn

| Input or action | Expected | Actual | Result |
|---|---|---|---|
| 4532015112830366 | Correct format, sum 50, passes | PASSES, sum 50 | Pass |
| 4532015112830367 | Correct format, sum 51, fails | FAILS, sum 51 | Pass |
| 0000000000000018 | Correct format, leading zeros kept, passes | PASSES, sum 10 | Pass |
| 453201511283036 | Reject: 15 digits | Invalid format message | Pass |
| 45320151128303666 | Reject: 17 digits | Invalid format message | Pass |
| 453201511283036X | Reject: non-digit | Invalid format message | Pass |
| 4532 015112830366 | Reject: internal space | Invalid format message | Pass |
| Several checks, then q | Each result correct, "Goodbye!" | Same | Pass |
| End of input | "End of input. Goodbye!", clean exit | Same | Pass |
| checkLuhn on a copy | Original string not changed | Not changed | Pass |
