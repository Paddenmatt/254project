#include <iostream>
#include <string>

using namespace std;

void display(string guess) {
	cout << "\nYour guess: \n";
	for (int i = 0; i < guess.length(); i++) {
		char color = guess[i];
		switch(toupper(color)) 
		{
			case 'R': cout << ansi::foreground::RED << "\u2B24 ";
					break;

			case 'W': cout << ansi::foreground::WHITE << "\u2B24 ";
					break;

			case 'Y': cout << ansi::foreground::YELLOW << "\u2B24 ";
					break;

			case 'G': cout << ansi::foreground::GREEN << "\u2B24 ";
					break;

			case 'B': cout << ansi::foreground::BLUE << "\u2B24 ";
					break;

			case 'M': cout << ansi::foreground::MAGENTA << "\u2B24 ";
					break;
		}
	}
	cout<< ansi::RESET << endl << endl;
}

void displaySol(char sol[]) {
	cout << "The correct answer is: \n";
	char color;
	for (int i = 0; i < 4; i++) {
		color = sol[i];
		switch(toupper(color)) 
		{
			case 'R': cout << ansi::foreground::RED << "\u2B24 ";
					break;

			case 'W': cout << ansi::foreground::WHITE << "\u2B24 ";
					break;

			case 'Y': cout << ansi::foreground::YELLOW << "\u2B24 ";
					break;

			case 'G': cout << ansi::foreground::GREEN << "\u2B24 ";
					break;

			case 'B': cout << ansi::foreground::BLUE << "\u2B24 ";
					break;

			case 'M': cout << ansi::foreground::MAGENTA << "\u2B24 ";
					break;
		}
	}
	cout<< ansi::RESET << endl << endl;
}