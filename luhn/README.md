# Luhn checksum validator — implementation plan

Separate console program (its own `main`), built from `luhn/main.cpp` + `luhn/luhn.cpp` with declarations in `luhn/luhn.h`.

## Planned functions

| Function | Job |
|---|---|
| `bool isValidFormat(const std::string& s)` | True only for exactly 16 characters, each `'0'`–`'9'`. No spaces, letters, or punctuation. |
| `int luhnSum(const std::string& digits)` | Walk from the rightmost digit leftward; double every second digit; if the doubled value > 9, subtract 9; return the total. Takes the input by `const` reference so the original is never modified. |
| `bool checkLuhn(const std::string& digits)` | Returns `luhnSum(digits) % 10 == 0`. |
| `main` | Loop: prompt → read a whole line → `q` exits → malformed input gets a format message and another try → well-formed input reports pass/fail. EOF exits cleanly. |

## Notes

- Input is read as a string so leading zeros are kept (e.g. `0000000000000018`).
- "Malformed input" and "well-formed but checksum fails" print different messages.
- A passing checksum only means the digits are consistent; it does not mean a card exists or is authorized.

## Required tests (from the handout)

| Input | Expected |
|---|---|
| `4532015112830366` | Format OK; passes (sum 50) |
| `4532015112830367` | Format OK; fails (sum 51) |
| `0000000000000018` | Format OK; leading zeros kept; passes |
| `453201511283036` | Reject: 15 digits |
| `45320151128303666` | Reject: 17 digits |
| `453201511283036X` | Reject: non-digit |
| Input with an internal space | Reject: malformed |
| Several checks, then exit | Correct results; clean exit |

Status: **not started** — will be implemented at Checkpoint 5 (`feature/luhn`).
