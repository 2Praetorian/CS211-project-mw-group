# Contributions

**Member:** Francisco Ibarra (GitHub: 2Praetorian), MW session, Group 99

I was removed from my original group, so I completed the whole project individually. Because there was no teammate, I was the author, reviewer, and merger on every pull request. Each PR has a written self-review describing what I built and tested before merging.

## Pull requests

| # | PR | What it added | Author | Reviewer | Merger | Checks I did |
|---|---|---|---|---|---|---|
| 1 | [Set up folders and group plan](https://github.com/2Praetorian/CS211-project-mw-group/pull/1) | README plan, course starter files, Luhn plan, .gitignore | 2Praetorian | 2Praetorian (self) | 2Praetorian | Compared starter files to the ones from class, checked .gitignore against GitHub's C++ template, no student IDs |
| 2 | [Add move_left with merge-once rule and row tests](https://github.com/2Praetorian/CS211-project-mw-group/pull/2) | move_left, row tests | 2Praetorian | 2Praetorian (self) | 2Praetorian | 7 of 7 row tests, three equal tiles, 2 2 4 0 0, played the game |
| 3 | [Add other directions, game controls, win and game over](https://github.com/2Praetorian/CS211-project-mw-group/pull/3) | right/up/down, scoring, menu, new game, win/game over, .h/.cpp split | 2Praetorian | 2Praetorian (self) | 2Praetorian | test_2048 21 of 21, played every command by hand |
| 4 | [Add save and load with full validation and sample save](https://github.com/2Praetorian/CS211-project-mw-group/pull/4) | savegame.txt save/load with validation, sample save | 2Praetorian | 2Praetorian (self) | 2Praetorian | test_2048 33 of 33, save/change/load round trip, bad files leave game unchanged |
| 5 | [Add Luhn checker](https://github.com/2Praetorian/CS211-project-mw-group/pull/5) | Luhn program and tests | 2Praetorian | 2Praetorian (self) | 2Praetorian | test_luhn 10 of 10, all required inputs by hand |
| 6 | [Final docs and package](https://github.com/2Praetorian/CS211-project-mw-group/pull/6) | README, tests.md, report.pdf, this file | 2Praetorian | 2Praetorian (self) | 2Praetorian | Clean build of both programs from a fresh download |

## Outside sources and tools

- **Course starter code:** `main.cpp` and `2048_helper.h` from class were the starting point for 2048.
- **GitHub's C++ .gitignore template**, plus a few project-specific lines.
- **Claude (AI):** Used Claude (AI) as a guide for planning, explaining concepts, drafting code, and drafting and reviewing the project report (report.pdf). I reviewed, tested, and committed all final code myself, and added my own hand-drawn diagrams to the report.
- My old group's earlier code was only looked at for reference. None of it was copied into this repo.

## How I checked the code

- Built both programs with `g++ -std=c++17 -Wall -Wextra -pedantic` with no warnings.
- Ran the automated tests in `tests/` (33 for 2048, 10 for Luhn) and recorded the results in `tests.md`.
- Played the game and ran the Luhn checker by hand for the controls and inputs in the handout.
- Checked that the dry runs in `report.pdf` match what the code actually does.
