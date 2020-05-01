/* Mastermind by Lewis Lam, Christophyer Ly, Derrick Lee
* Code based off of Michael Burdick
* This is an extremely simple version of the popular game Mastermind, which involves the computer randomly generating a series of four "pegs", all either Red, Orange, Yellow, Green, Blue, or Purple.
* The user then gets an alloted number of guesses to try and guess the series, referred to as the code. The only feedback the user recieves is two numbers: the number
* of pegs they have perfectly correct, and the number of pegs that are the right color, but in the wrong spot.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "colorkit.h"
#include "display.h"
#include "hintGenerator.h"
#include "timer.h"
#include "upperCaseifier.h"
#include "validGuess.h"
#include "leaderboard.h"
#include "savingscore.h"
#include <ctype.h>
#include <fstream>

// This is a comment

using namespace std;
void display(string guess);
void displaySol(char sol[]);

int main(){
	auto t1 = Clock::now();

	string choice = "";
	bool repeat = true;//we also set up repeat, which will determine for how long players want to keep playing the game
	int guesses;

	unsigned long totalTime;
	unsigned long bestTime = -1;
	unsigned long seconds;


	//save stream for the external file to save the high scores.
	int score = 0;

	//storing the current player's
	string currentPlayer = "";
	string currentScore = "";


	leaderboard();	// Displays the leaderboard



	do {	//I'm using a do-while loop here to contain the game, since I know players will want to play at least once.
		cout << "\nWelcome to Mastermind." << endl;
		string toggleTimer = "";
		string learn = "";
		bool showTutorial = false;


		cout << "\nLet us know who is playing!\n";
		cout << "Enter your three letter initials (Ex: MJP): ";
		cin  >> currentPlayer;

		while (currentPlayer.size() != 3){
			cout << "Please make sure your initials have 3 letters: ";
			cin  >> currentPlayer;
		}
		cout << '\n';

		cout << "Would you like to know how to play Mastermind? (y/n)" << endl;//there's a chance that the player actually has no idea how to play mastermind, so we offer to teach them
		cin >> learn;

		while (learn != "y" && learn != "Y" && learn != "n" && learn != "N") {//obviously, we have to validate this input, as well as reprompting every time the user gets it wrong
			cout << "Invalid input. Enter either 'y' or 'n': ";
			cin >> learn;
		}

		if (learn == "y" || learn == "Y") {//if the user wants a tutorial, we flip the switch to let them see it
			showTutorial = true;//if they don't due to the implementation, we actually don't have to do anything
		}

		if (showTutorial) {
			cout << string(109, '=') << '\n';
			cout << "|" << string(51, ' ') << "Rules" <<  string(51, ' ') << "|" << '\n';
			cout << string(109, '=') << '\n';
			cout << "- I will generate a random sequence of colored pegs, 4 long." << endl;
			cout << "- Each peg in the sequence is either RED (R), WHITE (W), ORANGE (O), GREEN (G), BLUE (B), or PURPLE (P)." << endl;
			cout << "- There may or may not be duplicates. " << endl;
			cout << "- You have a certain amount of guesses depending on the difficulty to try and determine this sequence." << endl;
			cout << "- Every time you guess, I'll tell you a bit of information." << endl;
			cout << "- Specifically, I'll tell you how many pegs you have of the right color AND location" << endl;
			cout << "- As well as how many pegs you have that are the right color, but wrong location." << endl;
			cout << "- You'll input your guesses as a sequence of the letters R, W, O, G, B, P. (ex. RBPY)." << endl;
			cout << "- If you don't guess the sequence within your alloted guesses, I win!" << endl;
			cout << string(109, '=') << '\n';
		}//This is the admittedly verbose tutorial


		cout << "\nPlease select a difficulty level:" << endl;
		cout << "1 = Easy. 2 = Medium. 3 = Hard. 4 = Extreme. 5 = Custom. ? = Difficulty Information." << endl;//We greet the player, then prompt them to select a difficulty
		cin >> choice;
		while (choice == "?") {
			cout << string(50, '=') << endl;
			cout << "|" << string(13, ' ') << "Difficulty Information" << string(13, ' ') <<  "|" << endl;
			cout << string(50, '=') << endl;
			cout << "Easy: 12 Guesses, No Timer" << endl;
			cout << "Medium: 10 Guesses, No Timer" << endl;
			cout << "Hard: 8 Guesses, No Timer" << endl;
			cout << "Extreme: 8 Guesses, 1 Minute" << endl;
			cout << "Custom: Custom Number of Guesses, Custom Timer" << endl;
			cout << string(50, '=') << endl << endl;
			cout << "Please select a difficulty level:" << endl;
			cout << "1 = Easy. 2 = Medium. 3 = Hard. 4 = Extreme. 5 = Custom. ? = Difficulty Information." << endl;
			cin >> choice;
		}


		while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "?"){//if the choice that they select isn't a valid one, then we slap them on the wrist and ask again
			cout << "Invalid choice. Please enter a 1, 2, 3, 4, 5, or ?: ";
			cin >> choice;
		}

		/* Most of my input validation takes the above form, where a single cin statement is followed by a while loop, with the conditional "as long as input isn't this or this or this or this"
		* I'm not 100% a fan of this, but it's a little cleaner to read than a do-while loop, because were I to use a do-while loop, I'd need another conditional inside to determine whether or not
		* to show an error message. This way, everything involving the user inputting something correct is all nice and snug together in a single block of code
		*/
		timer t;
		if (choice == "1"){
			guesses = 12;
			cout << "Easy selected!" << endl;
		}
		else if (choice == "2"){
			guesses = 10;
			cout << "Medium selected!" << endl;
		}
		else if (choice == "3"){
			guesses = 8;
			cout << "Hard selected!" << endl;
		}
		else if (choice == "4") {
			guesses = 8;
			toggleTimer = "Y";
			seconds = 60;
			cout << "Extreme selected!" << endl;
		}//The difficulty chosen determines the number of guesses the codebreaker has. We also acknowledge what difficulty option the player selected
		else {
			cout << "Custom selected!" << endl;
			cout << "Input number of guesses: ";
			cin >> guesses;
			cin.clear();
			cin.ignore();
			while(guesses <= 0) {
				cout << "Invalid input, pick a number greater than 0.\n";
				cin >> guesses;
				cin.clear();
				cin.ignore();
			}
			while (upperCaseifier(toggleTimer) != "Y" && upperCaseifier(toggleTimer) != "N") {
				cout << "Timer? (y/n)" << endl;
				cin >> toggleTimer;
				if (upperCaseifier(toggleTimer) == "Y") {
					cout << "Timer activated!" << endl;
					cout << "Enter the amount of time in minutes (Whole Numbers Only): ";
					cin >> seconds;
					seconds *= 60;
				}
				else if (upperCaseifier(toggleTimer) == "N") {
					cout << "Timer deactivated!" << endl;
				}
				else {
					cout << "Invalid choice. Please enter y or n" << endl;
				}
			}
		}//Allows the player to set the number of guesses, toggle the timer and set the amount of time

		char solution [4];//Now we're hitting the game itself. First we initialize a solution character array of length 4

		int numRed = 0, numOrange = 0, numYellow = 0, numGreen = 0, numBlue = 0, numPurple = 0;
		srand(time(0));//Also, seed our random number generator using the time.

		for (int i = 0; i < 4; i++){//for every character in our code
			if(rand() % 6 == 0){//generate a random number, then determine if it's odd or even
				solution[i] = 'R';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numRed++;//we also adjust our counter variables accordingly
			}
			else if (rand() % 6 == 1) {//generate a random number, then determine if it's odd or even
				solution[i] = 'W';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numOrange++;//we also adjust our counter variables accordingly
			}
			else if (rand() % 6 == 2) {//generate a random number, then determine if it's odd or even
				solution[i] = 'O';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numYellow++;//we also adjust our counter variables accordingly
			}
			else if (rand() % 6 == 3) {//generate a random number, then determine if it's odd or even
				solution[i] = 'G';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numGreen++;//we also adjust our counter variables accordingly
			}
			else if (rand() % 6 == 4) {//generate a random number, then determine if it's odd or even
				solution[i] = 'B';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numBlue++;//we also adjust our counter variables accordingly
			}
			else {//generate a random number, then determine if it's odd or even
				solution[i] = 'P';//using that data, we randomly assign every peg in the solution array to the appropriate color
				numPurple++;//we also adjust our counter variables accordingly
			}
		}
		string guess;
		bool correct = false;
		int k = 0;
		t.start();
		//Now that the code has been generated by our codemaker, time to let the player have at it
		while (k < guesses && !correct){//this while loop is basically a for loop that players can break out of early if they guess the code
			//I guess a break statement would have allowed me to just use a for loop, but I like having all of the break conditions right there in my loop header
			cout << "Enter a guess: ";//Prompt the user for a guess
			cin >> guess;
			while (!validGuess(guess)){//Once we have a guess, we validate it using the validGuess function. If it's not valid, we keep prompting until we get one that is
				cout << "Invalid input. Please enter a four-character input consisting solely of R, W, O, G, B, or P" << endl;
				cout << "Enter a guess: ";
				cin >> guess;
			}
			display(guess);

			correct = hintGenerator(upperCaseifier(guess), solution, numRed, numOrange, numYellow, numGreen, numBlue, numPurple);//now, take an all-uppercase version of the guess, the codemaker's code, and the total of each colored peg in the code
			//and run them through hintGenerator to create the hints, and also to determine if the codebreaker has successfully broken the code
			k++;//increment the iterator for our weird, janky for-loop
			if(correct){//If they're right, then go ahead and tell them they won
				displaySol(solution);
				totalTime = t.elapsedTime();
				cout << "That's exactly it, you win!" << endl;
				cout << "You beat Mastermind on ";
				if (choice == "1") { cout << "Easy"; }
				else if (choice == "2") { cout << "Medium"; }
				else if (choice == "3") { cout << "Hard"; }
				else if (choice == "4") { cout << "Extreme"; }
				else { cout << "Custom"; }
				cout << " Difficulty";
				cout << " in " << k << " guesses!" << endl;

				cout << "YOUR TIME: " << totalTime / 60 << ":";
				totalTime % 60 == 0 ? cout << "00\n" : cout << totalTime % 60 << endl;
				if (bestTime > totalTime || bestTime == -1) {
					bestTime = totalTime;
					cout << "NEW BEST TIME: " << bestTime / 60 << ":";
					bestTime % 60 == 0 ? cout << "00\n" : cout << bestTime % 60 << endl;
				}
				cout << "BEST TIME: " << bestTime / 60 << ":";
				bestTime % 60 == 0 ? cout << "00\n" : cout << bestTime % 60 << endl;

				// Score calculation (Easy = x1, Medium = x2, Hard = x4, Extreme = x8)
				// Base score of 200 * Difficulty Multiplier * Number of Guesses Left
				if (choice == "1"){	// Easy Difficulty Multiplier of x1
					score = (200 * (guesses - (k-1) ) );
				}
				else if (choice == "2"){	// Medium Difficulty Multiplier of x2
					score = (300 * 2 * (guesses - (k-1) ) );
				}
				else if (choice == "3"){	// Hard Difficulty Multiplier of x4
					score = (400 * 4 * (guesses - (k-1) ) );
				}
				else if (choice == "4"){	// Extreme Difficulty Multiplier of x8
					score = (500 * 8 * (guesses - (k-1) ) );
				}
				else	// Custom gets a score of 0
					score = 0;

				if (score > 9999){
					cout << "You achieved a score of 9999!\n"; // Dsiplay Max Score
				}
				else{
					cout << "You achieved a score of " << score << "!\n";
				}
			}

			else{//If they're not right, let them know, and tell them how many guesses they have left
				cout << "That's not it, sadly!" << endl;
				if (upperCaseifier(toggleTimer) == "Y") {
					if (t.isTimeout(seconds) == false) {
						cout << (seconds - t.elapsedTime()) / 60 << ":";
						if ((t.elapsedTime() % 60) < 50) {
							(seconds - t.elapsedTime()) % 60 == 0 ? cout << "00" : cout << (seconds - t.elapsedTime()) % 60;
						}
						else {
							(seconds - t.elapsedTime()) % 60 == 0 ? cout << "00" : cout << "0" << (seconds - t.elapsedTime()) % 60;
						}
						cout << " Remaining" << endl;
					}
					else {
						cout << "You ran out of time!" << endl;
						break;
					}
				}
				cout << "You have " << guesses - k << " guesse(s) left!" << endl << endl;
			}
		}

		if(!correct){//if we ended up breaking out of the while loop due to running out of guesses, instead of by guessing correctly, print the loss statement
			if (k >= guesses) {
				displaySol(solution);
				cout << "You're all out of guesses! I win!" << endl;
			}
			cout << "My code was ";
			for (int q = 0; q < 4; q++){//Also, we print out the code, to give users the catharsis of at least seeing the right code
				cout << solution[q];
			}
			cout << "!" << endl;
			cout << "\nSorry your score is 0\n";
		}

		cout << "Play again? (y/n) "; //Now that the game is complete, prompt the user to see if they want to play again
		string repeatchoice = "";
		cin >> repeatchoice;

		while(repeatchoice != "y" && repeatchoice != "Y" && repeatchoice != "n" && repeatchoice != "N"){//like all other user input, let's go ahead and validate this too
			cout << "Invalid input. Enter either 'y' or 'n': ";
			cin >> repeatchoice;
		}

		if(repeatchoice == "n" || repeatchoice == "N"){
			repeat = false;
		}//if our player says they don't wanna play anymore, we reverse repeat so we can break our do-while loop. If they do wanna continue, we do nothing, and let the loop...well, loop.
		cout << endl;

	} while(repeat);
	savescore(score, currentPlayer);

	leaderboard();
	return 0;
}
