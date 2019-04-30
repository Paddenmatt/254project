# Mastermind
A modified version of the Asylumrunner's Mastermind game with difficulty settings and timer options
Source: https://github.com/Asylumrunner/Mastermind

---
## About Mastermind
Mastermind is a board game invented in 1970 by Mordecai Meirowitz in which 2 players, the code breaker and the code maker, play against each other to see who is the Mastermind. Originally, the players would decide on a number guesses that the code breaker will have, but in this case the player will be able to choose specific difficulty levels or have a custom mode to set their own amount of guesses and a timer if desired.

---
## Instructions to Play
**NOTE: INSTRUCTIONS ARE GIVEN IN GAME AS WELL**
* The player will choose a specific difficulty level which will determine the number of guesses and if the timer is toggled on or off.
* The player will choose 4 colors ranging from Red (R), White(W), Yellow (Y), Green (G), Blue (B), and Magenta(M), with duplicated being allowed.
* The player will receive information based on their guess, one being how many colors are correct and in the correct spot, and how many colors are correct but in the wrong spot.
* This cycle will continue until the player runs out of guesses or has broken the code.
* A high score feature will show the time it took the player to solve the code and how it compares to a high score if there is one.

---
## Instructions To Run
To run in Linux...

in Linux Command Line (CTRL+ALT+T)...
// Go to directory where Mastermind.cpp is located
>> g++ Mastermind.cpp
>>
>>./a.out
