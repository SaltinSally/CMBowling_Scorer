// CMBowling_Scorer.cpp : Defines the entry point for the application.
//

#include "CMBowling_Scorer.h"
#include <array>;
#include <vector>;
#include <string>;
#include <cstring>;


int main()
{
	bool bkeepAsking = true;
	int nPlayerNum = 0;
	int nFrames = 10;
	int nBowls_Per_Frame = 3;
	std::string playerName;
	std::vector <std::string> names;

	// Captures player names and stores into a vector

	while (bkeepAsking)
	{
		char tempName[11];
		printf ("Enter the name of player %d, if you are done entering names type done and press enter\n"
				"Note the name of the player can not exceed 10 characters.\n", nPlayerNum+1);
		scanf("%10s", tempName);

		if (strcmp(tempName, "done") == 0) {
			bkeepAsking = false;
			system("cls");
		} else {
			playerName = tempName;
			names.push_back(playerName);
			nPlayerNum += 1;
			system("cls");
		}
	};

	int x = 1;
	for (auto i = names.begin(); i != names.end(); i++)
	{
		printf("Player %d: %s\n", x, i->c_str());
		x += 1;
		
	}
	printf("The number of players = %d", nPlayerNum);
	system("cls");

	// Total Number of Elements in 1D Array
	int nTotalElements = (nPlayerNum * nFrames * nBowls_Per_Frame);
	
	// Create a 1D Array
	int* scores = new int[nTotalElements];		// And Dynamically Allocate Memory

	// Function used to get the index of 1D Array
	auto getIndex = [nFrames, nBowls_Per_Frame](int player, int frame, int bowl) {
		return (player * nFrames * nBowls_Per_Frame) + (frame * nBowls_Per_Frame) + bowl;
		};

	// Loop over player names and capture number of pins knocked over after each bowl
	for (int player = 0; player < nPlayerNum; player++) {
		for (int frame = 0; frame < nFrames; frame++) {
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl); // Calculate the index
				if (bowl == 2 && !(frame == 9)) {
					scores[index] = 0;
				}
				if (bowl == 2 && frame == 9 && (scores[index - 2] + scores[index - 1]) >= 10) {
					std::cout << "Enter the number of pins knocked over for " << names[player]
						<< "\nFrame " << frame + 1
						<< "\nBowl " << bowl + 1 << ": ";
					std::cin >> scores[index]; // Store the score into the 1D array
					system("cls");
				} else if (bowl == 2) {
					scores[index] = 0;
				} else {
					std::cout << "Enter the number of pins knocked over for " << names[player]
						<< "\nFrame " << frame + 1
						<< "\nBowl " << bowl + 1 << ": ";
					std::cin >> scores[index]; // Store the score into the 1D array
					system("cls");
				}

			}
		}
	}


	int nArraySize = 
	// Output Bowling Scores
	std::cout << "\nBowling Scores:\n";
	for (int player = 0; player < nPlayerNum; player++) {
		for (int frame = 0; frame < nFrames; frame++) {
			std::cout << "Player " << names[player] << ", Frame " << frame + 1 << ": ";
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl);
				std::cout << scores[index] << " ";
			}
			std::cout << std::endl;
		}
	}

	// Deallocate the memory for 1D array
	delete[] scores;

	return 0;
}
