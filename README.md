# CS211 Project — 2048 + Luhn Validation (MW session)

Two separate C++17 console programs in one repository:

- **game2048/** — a playable 5x5 2048 game: slide/merge in four directions, score and move counter, win/game-over detection, and a single save slot (`savegame.txt`).
- **luhn/** — a validator that checks whether a 16-digit number passes the Luhn checksum. (Passing the checksum does not mean a card exists or is authorized.)

## Member

| Name | GitHub |
|---|---|
| _Your Name_ | [@2Praetorian](https://github.com/2Praetorian) |

Session: MW · Group: _GROUP ID_ · Repository: https://github.com/2Praetorian/CS211-project-mw-group

> Working as a one-person group. Student IDs are kept only in `group_info.txt` in the Blackboard ZIP, never in this repository.

## Task plan (six checkpoint PRs)

| # | Branch | Work | Status |
|---|---|---|---|
| 1 | `setup/project-plan` | README plan, starter files in `game2048/`, Luhn plan, `.gitignore` | in review |
| 2 | `feature/move-left` | `move_left` sliding + merge-once rule + row-example tests | to do |
| 3 | `feature/other-directions` | right/up/down, insert one `2` only after a changing move, score, move count, full menu (u/d/l/r/s/o/n/h/e), win and game-over; split into `2048_helper.h` / `2048_helper.cpp` | to do |
| 4 | `feature/save-load` | `savegame.txt` (`CS211_2048_V1` format), full validation, failed loads leave the game unchanged | to do |
| 5 | `feature/luhn` | Luhn validator, input validation, repeat loop | to do |
| 6 | `docs/final-package` | README, `tests.md`, `contributions.md`, report (dry runs + Luhn diagrams), clean-build test | to do |

## Current state

The `game2048/` folder holds the **unmodified course starter** (`main.cpp`, `2048_helper.h`). Its movement functions are empty, it inserts a tile after every command (even unchanged moves), it may insert a 4, and it has no score, save/load, or file split yet. Those are fixed in checkpoints 2–4. The Luhn program has not been started.

Build and run instructions will be added once the programs compile as specified.
