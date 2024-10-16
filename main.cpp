/***************************************************************
# main.cpp
# Main file for word search program, manages input/output and initiates search
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 16/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.10.1    15.10.2024   Initial version, integrates grid search and trie
# 2024.10.2    16.10.2024   Fix NaN problem
# 2024.10.3    16.10.2024   Remove all spaces from loaded words and ignore list
# 2024.10.4    16.10.2024   Added Switches to simplyfy options
****************************************************************/

#include "gridsearch.h"
#include "trie.h"
#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>  // For exception handling
#include <cstring>    // For strcmp

using namespace std;

// Function to display help information
void displayHelp()
{
    cout << "Usage: ./program <csv_grid_file> <csv_words_file> [options]\n"
         << "Options:\n"
         << "  -i <csv_ignore_words_file>   Specify a CSV file with words to ignore (optional)\n"
         << "  -n <min_word_length>         Specify the minimum word length to search for (optional, default: 3)\n"
         << "  -h                           Display this help message\n"
         << endl;
}

int main(int argc, char* argv[])
{
    // Check if the help flag is present
    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0)  // If -h flag is found, display help and exit
        {
            displayHelp();
            return 0;
        }
    }

    // Check if at least two file names were passed as command-line arguments (grid and words file)
    if (argc < 3)
    {
        cerr << "Error: Not enough arguments provided. Use -h for help.\n";
        return 1;
    }

    string csvFileName = argv[1];   // Get the CSV grid file name from the command-line argument
    string wordsFileName = argv[2]; // Get the CSV dictionary file name from the second argument

    set<string> ignoreWords;  // Set to store ignore words (initially empty)
    int minWordLength = 3;    // Default minimum word length

    // Parse additional optional arguments
    for (int i = 3; i < argc; ++i)
    {
        if (strcmp(argv[i], "-i") == 0)  // Check for ignore words file switch
        {
            if (i + 1 < argc)  // Ensure there is a file name after the switch
            {
                string ignoreFileName = argv[++i];
                ignoreWords = loadIgnoreWordsFromCSV(ignoreFileName);
            }
            else
            {
                cerr << "Error: No ignore words file specified after -i." << endl;
                return 1;
            }
        }
        else if (strcmp(argv[i], "-n") == 0)  // Check for minimum word length switch
        {
            if (i + 1 < argc)  // Ensure there is a number after the switch
            {
                try
                {
                    minWordLength = stoi(argv[++i]);  // Get the minimum word length
                }
                catch (const invalid_argument& e)
                {
                    cerr << "Error: Invalid minimum word length provided. It must be a number." << endl;
                    return 1;
                }
            }
            else
            {
                cerr << "Error: No minimum word length specified after -n." << endl;
                return 1;
            }
        }
        else
        {
            cerr << "Error: Unknown option " << argv[i] << endl;
            return 1;
        }
    }

    // Create and initialize a Trie
    Trie myTrie;

    // Load the words from the CSV dictionary file into the Trie
    loadWordsFromCSVFile(wordsFileName, myTrie);

    // Read the CSV file and populate the grid
    vector<vector<char>> grid = readCSVFile(csvFileName);

    // Check if the grid was successfully loaded
    if (grid.empty())
    {
        cerr << "Error: Grid could not be loaded from CSV file." << endl;
        return 1;  // Exit with error
    }

    // Create a GridSearch object
    GridSearch gridSearch;

    // Vector to store found words and their locations (start and end)
    vector<pair<string, pair<pair<int, int>, pair<int, int>>>> wordLocations;

    // Use GridSearch to find all words in the grid that are in the Trie, along with their locations
    vector<string> foundWords = gridSearch.searchWords(grid, &myTrie, wordLocations, ignoreWords, minWordLength);

    // Output the found words and their starting and ending locations
    cout << "Found words and their locations: " << endl;
    for (const auto& entry : wordLocations)
    {
        cout << "Word: " << entry.first << " from position (" << entry.second.first.first << ", " << entry.second.first.second
             << ") to position (" << entry.second.second.first << ", " << entry.second.second.second << ")" << endl;
    }

    return 0;
}
