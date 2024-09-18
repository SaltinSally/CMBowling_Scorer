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
	int* scores = new int[nTotalElements];		// And Dynamically Allocate Memory

	// Function used to get the index of 1D Array
	auto getIndex = [nFrames, nBowls_Per_Frame](int player, int frame, int bowl) {
		return (player * nFrames * nBowls_Per_Frame) + (frame * nBowls_Per_Frame) + bowl;
		};


	/*
		  _______ ____    _____   ____    
		 |__   __/ __ \  |  __ \ / __ \ _ 
			| | | |  | | | |  | | |  | (_)
			| | | |  | | | |  | | |  | |  
			| | | |__| | | |__| | |__| |_ 
			|_|  \____/  |_____/ \____/(_)
                                  
         Fix logic. Right now it scores an entire game for one player, then an entire game for the next.
		 This should be adjusted so every game runs concurrently, as it would in a real bowling game.

	*/


	// Loop over player names and capture number of pins knocked over after each bowl
	for (int player = 0; player < nPlayerNum; player++) {
		for (int frame = 0; frame < nFrames; frame++) {
			for (int bowl = 0; bowl < nBowls_Per_Frame; bowl++) {
				int index = getIndex(player, frame, bowl); // Calculate the index
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
					system("cls");
				}

			}
		}
	}

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

int scanner(const char* data, char* buffer, size_t buflen)
{
	char format[32];
	if (buflen == 0)
		return 0;
	snprintf(format, sizeof(format), "%%%ds", (int)(buflen - 1));
	return sscanf(data, format, buffer);
}

