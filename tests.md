# Test Record

## 2048 - move_left (Checkpoint 2)

Run with `tests/test_move_left.cpp`. Each row is tested in the top row of an empty board. These results are before any random tile gets added.

| Start row | Expected | Score | Actual | Pass/Fail |
|---|---|---|---|---|
| 0 2 0 2 0 | 4 0 0 0 0 | +4 | 4 0 0 0 0, +4 | Pass |
| 2 2 2 0 0 | 4 2 0 0 0 | +4 | 4 2 0 0 0, +4 | Pass |
| 2 2 2 2 2 | 4 4 2 0 0 | +8 | 4 4 2 0 0, +8 | Pass |
| 2 2 4 0 0 | 4 4 0 0 0 | +4 | 4 4 0 0 0, +4 | Pass |
| 4 4 8 8 0 | 8 16 0 0 0 | +24 | 8 16 0 0 0, +24 | Pass |
| 2 4 8 0 0 | 2 4 8 0 0 (no change) | +0 | 2 4 8 0 0, +0, no change | Pass |
| 0 0 0 0 2 | 2 0 0 0 0 (slide, no merge) | +0 | 2 0 0 0 0, +0, changed | Pass |

Result: 7 of 7 passed.

Notes:
- 2 2 2 0 0 and 2 2 2 2 2 check that no tile merges twice in one move.
- 2 2 4 0 0 checks that the new 4 doesn't merge with the 4 next to it.