#ifndef HINTGENERATOR_H
#define HINTGENERATOR_H
/*This function gives both a hint and check how many
  colors you have guessed correctly and how many colors
  you have in the correct position
*/
//This function generates hints when inforrec
bool hintGenerator(string guess, char* solution, int numR, int numO, int numY, int numG, int numB, int numP){//hintGenerator both creates the hints that the codebreaker will recieve, and also checks to see if the codebreaker has guessed the code
	//Assume the players guess is correct unless proven otherwise
	bool exactlyAlike = true;
	//Keep running total number of pegs that are in the right spot and correct color
	//and the pegs that are in the wrong spot but the correct color
	int rightColorAndPlacement = 0;
	int rightColorWrongSpot = 0;
	int wrongRedGuessed = 0, wrongOrangeGuessed = 0, wrongYellowGuessed = 0, wrongGreenGuessed = 0, wrongBlueGuessed = 0, wrongPurpleGuessed = 0;//these counter variables will track the number of incorrectly-placed pegs, for use in the second hint
	//This checks every letter of the guess
	for(int i = 0; i < 4; i++){
		//Checks to see if it matches the peg that the computer is on. If it is then
		if(guess[i] == solution[i]){
			//Increments the number of correct pegs by one
			rightColorAndPlacement++;
			//These if and else if statement are to check if you guessed a color
			//correctly, but in the wrong place
			if(guess[i] == 'R') {
				numR--;
			}
			else if(guess[i]== 'W') {
				numO--;
			}
			else if (guess[i] == 'Y') {
				numY--;
			}
			else if (guess[i] == 'G') {
				numG--;
			}
			else if (guess[i] == 'B') {
				numB--;
			}
			else if (guess[i] == 'M') {
				numP--;
			}
		}
		//This statement is if the guess and the peg are not the same
		else{
			//We would make exactlyAlike false because we found out that they arent the same.
			exactlyAlike = false;
			//We record that we have an incorrect peg in its appropriate color variable
			if(guess[i] == 'R' ){
				wrongRedGuessed++;
			}
			else if(guess[i]== 'W' ){
				wrongOrangeGuessed++;
			}
			else if (guess[i] == 'Y') {
				wrongYellowGuessed++;
			}
			else if (guess[i] == 'G') {
				wrongGreenGuessed++;
			}
			else if (guess[i] == 'B') {
				wrongBlueGuessed++;
			}
			else if (guess[i] == 'M') {
				wrongPurpleGuessed++;
			}
		}


	}

	/* Now that we've fully iterated over the two codes, we have the exact number of perfect pegs in our player's guess. How, then, do we get the number of pegs which are of the right color, but wrong spot?
	* Simple. We compare the number of colored pegs remaining unguessed in the code against the number of white and black pegs the player guessed that were not matches.
	* If the number of incorrect pegs of color X is greater than or equal to the number of pegs of color X remaining in the solution, then we note that all remaining pegs of color X have been identified, if not
	* properly placed. If the number of incorrect pegs of color X is less than the number of pegs of color X remaining in the solution, we only return the number of pegs of color X that the player managed to
	* include in their solution.
	*/


	if (wrongRedGuessed >= numR) {
		rightColorWrongSpot += numR;
	}
	else {
		rightColorWrongSpot += wrongRedGuessed;
	}

	if (wrongOrangeGuessed >= numO) {
		rightColorWrongSpot += numO;
	}
	else {
		rightColorWrongSpot += wrongOrangeGuessed;
	}

	if (wrongYellowGuessed >= numY) {
		rightColorWrongSpot += numY;
	}
	else {
		rightColorWrongSpot += wrongYellowGuessed;
	}

	if (wrongGreenGuessed >= numG) {
		rightColorWrongSpot += numG;
	}
	else {
		rightColorWrongSpot += wrongGreenGuessed;
	}

	if (wrongBlueGuessed >= numB) {
		rightColorWrongSpot += numB;
	}
	else {
		rightColorWrongSpot += wrongBlueGuessed;
	}

	if (wrongPurpleGuessed >= numP) {
		rightColorWrongSpot += numP;
	}
	else {
		rightColorWrongSpot += wrongPurpleGuessed;
	}

	//These two cout statements provide hints for the player
	cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;
	cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl;
	//Returns if the player's guess is correct or not
	return exactlyAlike;
}
#endif
