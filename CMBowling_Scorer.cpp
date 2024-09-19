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

    std::vector<std::string> names;

    printf("Enter the name of player %d, if you are done entering names press enter again\n"
        "Note the name of the player can not exceed 10 characters.\n",
        nPlayerNum + 1);

    std::string name;

    do {
        std::getline(std::cin, name);

        if (!name.empty()) {
            names.push_back(name);
            nPlayerNum += 1;
            printf("Enter the name of player %d, if you are done entering names press enter again\n",
                nPlayerNum + 1);
        }

    } while (!name.empty());

    CLEAR();

    int n = 1;
    std::for_each(names.begin(), names.end(), [&n](std::string name) {
        printf("Player %d: %s\n", n, name.c_str());
        n++;
        });

    putchar('\n');

    // Total Number of Elements in 1D Array
    int nTotalElements = (nPlayerNum * nFrames * nBowls_Per_Frame);

    // Create a 1D Array
    int* scores = new int[nTotalElements]; // Dynamically Allocate Memory
    std::fill(scores, scores + nTotalElements, 0); // Initialize scores to zero

    // Function used to get the index of 1D Array
    auto getIndex = [nFrames, nBowls_Per_Frame](int player, int frame, int bowl) {
        return (player * nFrames * nBowls_Per_Frame) + (frame * nBowls_Per_Frame) + bowl;
        };

    // Loop over player names and capture number of pins knocked over after each bowl
    for (int frame = 0; frame < nFrames; frame++) {
        for (int player = 0; player < nPlayerNum; player++) {
            int index = getIndex(player, frame, 0);
            int firstThrow = 0, secondThrow = 0, thirdThrow = 0;

            // Input first throw
            std::cout << "Enter the number of pins knocked over for " << names[player]
                << "\nFrame " << frame + 1 << "\nBowl 1: ";
            std::cin >> firstThrow;

            // If strike in frames 1-9
            if (firstThrow == 10 && frame < 9) {
                scores[index] = 10;
                scores[index + 1] = 0;
            }
            else {
                // Input second throw
                std::cout << "Enter the number of pins knocked over for " << names[player]
                    << "\nFrame " << frame + 1 << "\nBowl 2: ";
                std::cin >> secondThrow;
                scores[index] = firstThrow;
                scores[index + 1] = secondThrow;
            }

            // Handle third throw in the 10th frame
            if (frame == 9 && (firstThrow + secondThrow >= 10)) {
                std::cout << "Enter the number of pins knocked over for " << names[player]
                    << "\nFrame " << frame + 1 << "\nBowl 3: ";
                std::cin >> thirdThrow;
                scores[index + 2] = thirdThrow;
            }
            else {
                scores[index + 2] = 0;
            }

            CLEAR();
        }
    }

    // Calculate Total Scores
    std::vector<int> playertotals(nPlayerNum, 0);

    for (int player = 0; player < nPlayerNum; player++) {
        int totalScore = 0;
        int playerStartIndex = player * nFrames * nBowls_Per_Frame;

        for (int frame = 0; frame < nFrames; frame++) {
            int index = playerStartIndex + frame * nBowls_Per_Frame;
            int firstThrow = scores[index];
            int secondThrow = scores[index + 1];
            int thirdThrow = scores[index + 2];
            int frameScore = 0;

            if (frame < 9) {
                // Strike
                if (firstThrow == 10) {
                    int nextIndex = playerStartIndex + (frame + 1) * nBowls_Per_Frame;
                    int nextFirstThrow = scores[nextIndex];
                    int nextSecondThrow;

                    if (nextFirstThrow == 10 && frame + 1 < 9) {
                        int nextNextIndex = playerStartIndex + (frame + 2) * nBowls_Per_Frame;
                        nextSecondThrow = scores[nextNextIndex];
                    }
                    else if (nextFirstThrow == 10 && frame + 1 == 9) {
                        nextSecondThrow = scores[nextIndex + 1];
                    }
                    else {
                        nextSecondThrow = scores[nextIndex + 1];
                    }

                    frameScore = 10 + nextFirstThrow + nextSecondThrow;
                }
                // Spare
                else if (firstThrow + secondThrow == 10) {
                    int nextIndex = playerStartIndex + (frame + 1) * nBowls_Per_Frame;
                    int nextFirstThrow = scores[nextIndex];
                    frameScore = 10 + nextFirstThrow;
                }
                // Open Frame
                else {
                    frameScore = firstThrow + secondThrow;
                }
            }
            else {
                // 10th Frame
                frameScore = firstThrow + secondThrow + thirdThrow;
            }

            totalScore += frameScore;
        }

        playertotals[player] = totalScore;
    }

    // Output Bowling Scores
    std::cout << "\nBowling Scores:\n";
    for (int player = 0; player < nPlayerNum; player++) {
        std::cout << "Player " << names[player] << ":\n";
        for (int frame = 0; frame < nFrames; frame++) {
            int index = getIndex(player, frame, 0);
            std::cout << "Frame " << frame + 1 << ": "
                << scores[index] << " "
                << scores[index + 1] << " "
                << (frame == 9 ? std::to_string(scores[index + 2]) : "") << "\n";
        }
        std::cout << "Total Score: " << playertotals[player] << "\n\n";
    }

    // Deallocate the memory for 1D array
    delete[] scores;

    return 0;
}
