/***************************************************************
# main.cpp
# Main file for word search program, manages input/output and initiates search
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 15/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.1.0     15.10.2024   Initial version, integrates grid search and trie
****************************************************************/

#include "gridsearch.h"
#include "trie.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[])
{
    // Check if at least three file names were passed as command-line arguments
    if (argc < 4)
    {
        cerr << "Error: Not enough arguments provided. Usage: ./program <csv_grid_file> <csv_words_file> [<csv_ignore_words_file>] <min_word_length>" << endl;
        return 1;
    }

    string csvFileName = argv[1];   // Get the CSV grid file name from the command-line argument
    string wordsFileName = argv[2]; // Get the CSV dictionary file name from the second argument

    // Create and initialize a Trie
    Trie myTrie;

    // Load the words from the CSV dictionary file into the Trie
    loadWordsFromCSVFile(wordsFileName, myTrie);

    // Set to store ignore words (initially empty)
    set<string> ignoreWords;

    // Check if the third argument (ignore words file) is provided
    if (argc >= 4)
    {
        string ignoreFileName = argv[3]; // Get the CSV file with words to ignore
        ignoreWords = loadIgnoreWordsFromCSV(ignoreFileName); // Load ignore words
    }

    // Read the minimum word length from the 4th parameter
    int minWordLength = argc == 5 ? stoi(argv[4]) : 3;

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
