#ifndef SAVINGSCORE_H
#define SAVINGSCORE_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

void savescore(int score, string currentPlayer) {
    string temp = "";
	string Array[10][2];
	int count = 0;

	

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
		Array[count][0] = tempName;
		Array[count][1] = tempScore;

		count++;
	}
    savefile.close();

    int huntcount = 0;
    //checking the leaderboard if the score is high enough
    
    for(int i = 9; i > -1; i--)
    {
        if(score > std::stoi(Array[i][1]))
        {
			string tempuser = Array[i][0];
			string tempscore = Array[i][1];

			if( i == 0)
			{
				Array[i][0] = currentPlayer;
            	Array[i][1] = std::to_string(score);
            	i = -1;
			}
			else
			{
				Array[i][0] = currentPlayer;
            	Array[i][1] = std::to_string(score);

				for(int leftover = i-1; leftover >= 0; leftover--)
				{
					cout << "HERE2" << endl;

					string temp2user = Array[leftover][0];
					string temp2score = Array[leftover][1];

					
					Array[leftover][0] = tempuser;
					Array[leftover][1] = tempscore;

					tempuser = temp2user;
					tempscore = temp2score;
				}
				i = -1;
			}
        }
    }
	
	//write the array to file
	
	ofstream savetofile;
	savetofile.open ("save.txt", std::ofstream::trunc);
	//savefile << "did this overwrite? \n";
	
	
	
	for(int j = 0; j< 10; j++)
	{
		savetofile << Array[j][0] << " " << Array[j][1] << endl;
		
	}

	savetofile.close();
}



#endif