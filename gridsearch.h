#ifndef HEADER_AEA786E94F229B
#define HEADER_AEA786E94F229B

/***************************************************************
# gridsearch.h
# Header for gridsearch.cpp, defines GridSearch class and related functions
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 16/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.10.1    15.10.2024   Initial implementation of GridSearch class
# 2024.10.2    16.10.2024   Fixed issue with NaN entries in word list loading
# 2024.10.3    16.10.2024   Removed spaces from loaded words and ignore list
****************************************************************/

#ifndef GRIDSEARCH_H
#define GRIDSEARCH_H

#include <vector>
#include <string>
#include <set>
#include "trie.h"

class GridSearch
{
public:
    GridSearch();
    ~GridSearch();

    // Depth-first search (DFS) to find words in the grid using Trie.
    // Explores the grid in 8 possible directions (up, down, left, right, diagonals),
    // tracking valid words and their start and end positions in a 1-based index.
    void dfs(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, TrieNode* node, int x, int y, std::string word, std::vector<std::string>& result, std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& locations, std::set<std::string>& foundWords, const std::set<std::string>& ignoreWords, int minWordLength, int startX, int startY, int dirX, int dirY);

    // Search the grid for words in the Trie, respecting ignore words and minimum word length.
    // Stores the locations of found words with their start and end coordinates.
    std::vector<std::string> searchWords(std::vector<std::vector<char>>& grid, Trie* trie, std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& locations, const std::set<std::string>& ignoreWords, int minWordLength);
};

// Function to remove all spaces from a string, returning a new string without any spaces.
std::string removeAllSpaces(const std::string& str);

// Function to read a grid from a CSV file, assuming each cell contains a single character.
std::vector<std::vector<char>> readCSVFile(const std::string& filename);

// Function to load words from a CSV file into the Trie, ignoring NaN values and removing spaces.
void loadWordsFromCSVFile(const std::string& filename, Trie& trie);

// Function to load ignore words from a CSV file into a set, ignoring NaN values and removing spaces.
std::set<std::string> loadIgnoreWordsFromCSV(const std::string& filename);

#endif // GRIDSEARCH_H
#endif // header guard 

