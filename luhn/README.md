# Luhn Checker - Plan
This is the second program. It's separate from 2048 and has its own main.

## What it does
You type in a 16 digit number and it tells you if it passes the Luhn checksum. It keeps asking until you type q to quit.

## How I'm going to do it
- Read the number as a string so leading zeros don't get lost.
- First check the format: exactly 16 characters and all digits. If not, tell the user it's not formatted right and let them try again.
- Then run the Luhn check. Start at the last digit and double every second digit going left. If a doubled number is over 9, subtract 9. Add everything up, and if the total ends in 0 it passes.
- Keep the format check and the Luhn check in separate functions (checkLuhn does the math).

## Tests I need to pass
- 4532015112830366 - passes
- 4532015112830367 - fails
- 0000000000000018 - passes (leading zeros kept)
- 453201511283036 - rejected, only 15 digits
- 45320151128303666 - rejected, 17 digits
- 453201511283036X - rejected, has a letter
- a number with a space in it - rejected
- check a few numbers then quit - quits cleanly

Not started yet.
