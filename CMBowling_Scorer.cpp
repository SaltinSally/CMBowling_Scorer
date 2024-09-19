// CMBowling_Scorer.cpp : Defines the entry point for the application.
//

#include "CMBowling_Scorer.h"
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
	#define CLEAR() system("cls");
#elif __linux__
	#define CLEAR() system("clear");
#endif

int main()
{
	int nPlayerNum = 0;
	int nFrames = 10;
	int nBowls_Per_Frame = 3;
	int nNumBowls = 0;

	std::vector <std::string> names;

	printf ("Enter the name of player %d, if you are done entering names press enter again\n"
			"Note the name of the player can not exceed 10 characters.\n", nPlayerNum+1);
	
	std::string name;

	do {
			// getline grabs a string from cin, and discards any preexisting values in the variable
			std::getline(std::cin, name);

			if (!name.empty()) {
				// push_back creates a copy, meaning we can reuse name on the next loop
				names.push_back(name);
				nPlayerNum += 1;
			}

	} while (!name.empty());

	CLEAR();

	int n = 1;
	// for each value in the vector, print it to name. allow us to use n to count. 
	std::for_each(names.begin(), names.end(), [&n](std::string name) {
		printf("Player %d: %s\n", n, name.c_str());
		n++;
	});

	// extra newline for good luck :D
	putchar('\n');


	// Total Number of Elements in 1D Array
	int nTotalElements = (nPlayerNum * nFrames * nBowls_Per_Frame);
	
	// Create a 1D Array
	int* scores = new int[nTotalElements];		// Dynamically Allocate Memory

	// Function used to get the index of 1D Array
	auto getIndex = [nFrames, nBowls_Per_Frame](int player, int frame, int bowl) {
		return (player * nFrames * nBowls_Per_Frame) + (frame * nBowls_Per_Frame) + bowl;
		};


	// Loop over player names and capture number of pins knocked over after each bowl
	for (int frame = 0; frame < nFrames; frame++) {
		for (int player = 0; player < nPlayerNum; player++) {
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl); // Calculate the index
				nNumBowls += 1;
				if (bowl == 2 && !(frame == 9)) {
					scores[index] = 0;
				}
				if (bowl == 2 && frame == 9 && (scores[index - 2] + scores[index - 1]) >= 10) {
					std::cout <<  "Enter the number of pins knocked over for " << names[player]
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
					CLEAR();
				}

			}
		}
	}

	// Calculate Total Score

	std::vector<int> playertotals(nPlayerNum);
	int nBowlsPerPlayer = nNumBowls / nPlayerNum;
	int nNextTurn = (nPlayerNum * nBowls_Per_Frame);
	//int nArraySize = 5;
	// Output Bowling Scores
	for (int player = 0; player < nPlayerNum; player++) {
		for (int frame = 0; frame < nFrames; frame++) {
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl);
				if (bowl == 0 && frame == 9 && scores[index] == 10) {
					playertotals[player] += (scores[index] + scores[index + 1] + scores[index + 2]);
				}
				else if (bowl == 1 && frame == 9 && scores[index - 1] != 10 && (scores[index - 1] + scores[index]) == 10) {
					playertotals[player] += (scores[index-1] + scores[index] + scores[index + 1]);
				}
				else if (frame == 9 && bowl == 0) {
					playertotals[player] += scores[index] + scores[index + 1] + scores[index + 2];
				}
				else if (bowl == 0 && scores[index] == 10 && frame != 9) {
					playertotals[player] += scores[index + 1] + (scores[index + nNextTurn]);
				}
				else if (bowl == 1 && frame != 9 && scores[index - 1] != 10 && (scores[index - 1] + scores[index]) == 10) {
					playertotals[player] += scores[index] + scores[index + nNextTurn - 1];
				}
				else if (bowl == 0 && frame != 9 && scores[index] != 10 && (scores[index] + scores[index +1]) != 10) {
					playertotals[player] += scores[index] + scores[index + 1];
				}


			}
			std::cout << std::endl;
		}
	}




	std::cout << "\nBowling Scores:\n";
	for (int player = 0; player < nPlayerNum; player++) {
		for (int frame = 0; frame < nFrames; frame++) {
			std::cout << "Player " << names[player] << ", Frame " << frame + 1 << ": ";
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl);
				if (bowl == 3 && frame != 9);
				std::cout << scores[index] << " ";
				
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	for (int player = 0; player <= nPlayerNum; player++) {
		std::cout << "player " << names[player] << " scored: " << playertotals[player];
	}

	// Deallocate the memory for 1D array
	delete[] scores;

	return 0;
}

int scanner(const char* data, char* buffer, size_t buflen)
{
	char format[32];
	if (buflen == 0)
		return 0;
	snprintf(format, sizeof(format), "%%%ds", (int)(buflen - 1));
	return sscanf(data, format, buffer);
}

