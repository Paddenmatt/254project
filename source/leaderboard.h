#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void leaderboard(){

	//save stream for the external file to save the high scores.
	string temp = "";
	string Array[10][2];
	int count = 0;

	// Structure used for leaderboard header
	cout << '|' << string (21, '=')              << '|' << '\n';
	cout << '|' << "     Leaderboard     "       << '|' << '\n';
	cout << '|' << string (21, '=')              << '|' << '\n';
	cout << '|' << "   Name   " << "   Score   " << '|' << '\n';
	cout << '|' << string (21, '=')              << '|' << '\n';


	//opening stream to intake data
	ifstream savefile;
	savefile.open ("save.txt");

	//reading existing data from file ( AAA score)
	for(int h = 0; h < 10; h++)
	{
		getline(savefile, temp);
		string tempName = "";
		string tempScore = "";
		for(int i = 0; i < 3; i++)
		{
			tempName += temp[i];
		}
		for(int j = 4; j < 8; j++)
		{
			tempScore += temp[j];
		}

		//reading name to array
		Array[count][0] = tempName;

		//reading score to array
		string add = "0";
		if(stoi(tempScore) < 1000 && stoi(tempScore) > 0)
		{
			Array[count][1] = add.append(tempScore);
		}
		else
		{
			Array[count][1] = tempScore;
		}

		
		cout << "|   " << setw(10) << left << Array[count][0] << setw(8) << left << Array[count][1] << "|"<< endl;
		count++;
	}

	// Closes bottom of the leaderboard
	cout << '|' << string (21, '=') << '|' << '\n';


	savefile.close();

	// ofstream savefile;
	// savefile.open ("save.txt");
	// savefile << "did this overwrite? \n";
	// savefile.close();

}

#endif
