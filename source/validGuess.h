bool validGuess (string guess){
	//If the player did not insert exactly 4 guesses long, it returns false.
	if(guess.length() != 4){
		return false;
	}
	//If it is four letters long, then it would go through this for loop
	for(int j = 0; j < 4; j++){
		//This if loop checks check to see if you inputted the correct
		//letters, which are R, r, W, w, Y, y, G, g, B, b, M, and m
		if(toupper(guess[j]) != 'R' && toupper(guess[j]) != 'W' && toupper(guess[j]) != 'O' && toupper(guess[j]) != 'G' && toupper(guess[j]) != 'B' && toupper(guess[j]) != 'P'){
			//If one of the four letters is incorrect, then it would return false
			return false;
		}
	}
	//If it passed both tests, it would be a valid guess from the player
	return true;

}
