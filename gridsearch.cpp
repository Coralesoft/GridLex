/***************************************************************
# gridsearch.cpp
# Code implementing DFS-based grid search with Trie for word finding
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 15/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.1.0     15.10.2024   Initial implementation of grid search using DFS
****************************************************************/

#include "gridsearch.h"
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor
GridSearch::GridSearch() {}

// Destructor
GridSearch::~GridSearch() {}

// Define the directions for 8 possible moves in the grid (up, down, left, right, and diagonals)
int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};

// DFS function implementation with location tracking, ignore words, and minimum word length
void GridSearch::dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, TrieNode* node, int x, int y, string word, vector<string>& result, vector<pair<string, pair<pair<int, int>, pair<int, int>>>>& locations, set<string>& foundWords, const set<string>& ignoreWords, int minWordLength, int startX, int startY, int dirX, int dirY)
{
    if (x < 0 || y < 0 || static_cast<size_t>(x) >= grid.size() || static_cast<size_t>(y) >= grid[0].size() || visited[x][y])
    {
        return;  // Out of bounds or already visited
    }

    char c = grid[x][y];
    int index = toupper(c) - 'A';  // Ensure the character is uppercase

    if (node->children[index] == nullptr)
    {
        return;  // No further path in the Trie for this character
    }

    word += c;  // Append the character to the current word
    node = node->children[index];  // Move to the next Trie node

    // Check if the word is in ignoreWords and if its length meets the minimum requirement
    if (node->isEndOfWord && foundWords.find(word) == foundWords.end() && ignoreWords.find(word) == ignoreWords.end() && word.length() >= static_cast<size_t>(minWordLength))
    {
        // Only add the word if it hasn't been found already, it's not in the ignore list, and it meets the min word length requirement
        result.push_back(word);  // Valid word found
        // Track both the starting and ending positions (1-based indexing)
        locations.push_back({word, {{startX + 1, startY + 1}, {x + 1, y + 1}}});
        foundWords.insert(word);  // Add the word to the set of found words
    }

    visited[x][y] = true;  // Mark cell as visited

    // Explore the current direction only
    dfs(grid, visited, node, x + dirX, y + dirY, word, result, locations, foundWords, ignoreWords, minWordLength, startX, startY, dirX, dirY);

    visited[x][y] = false;  // Backtrack
}

// Main function to search the grid for words in the Trie, with location tracking, ignore words, and minimum word length
vector<string> GridSearch::searchWords(vector<vector<char>>& grid, Trie* trie, vector<pair<string, pair<pair<int, int>, pair<int, int>>>>& locations, const set<string>& ignoreWords, int minWordLength)
{
    vector<string> result;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));  // Initialize visited array
    set<string> foundWords;  // Set to track unique found words

    // Start DFS from each cell in the grid and explore all 8 directions
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            for (int d = 0; d < 8; d++)    // Explore all 8 directions
            {
                dfs(grid, visited, trie->root, i, j, "", result, locations, foundWords, ignoreWords, minWordLength, i, j, dx[d], dy[d]);
            }
        }
    }

    return result;  // Return all unique found words
}

// Function to read the grid from a CSV file
vector<vector<char>> readCSVFile(const string& filename)
{
    vector<vector<char>> grid;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV file " << filename << endl;
        return grid;
    }

    string line;
    while (getline(file, line))
    {
        vector<char> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ','))
        {
            if (!cell.empty())
            {
                char upperChar = toupper(cell[0]);  // Convert to uppercase
                row.push_back(upperChar);  // Assuming each cell contains a single character
            }
        }

        if (!row.empty())
        {
            grid.push_back(row);
        }
    }

    file.close();
    return grid;
}

// Function to load the words from the CSV file into the Trie
void loadWordsFromCSVFile(const string& filename, Trie& trie)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV words file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;

        while (getline(ss, word, ','))
        {
            if (!word.empty() && word.length() >= 3)    // Check for minimum length of 3
            {
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                trie.insert(word);
            }
        }
    }

    file.close();
}

// Function to load ignore words from the CSV file into a set
set<string> loadIgnoreWordsFromCSV(const string& filename)
{
    set<string> ignoreWords;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open ignore words CSV file " << filename << endl;
        return ignoreWords;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;

        while (getline(ss, word, ','))
        {
            if (!word.empty())
            {
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                ignoreWords.insert(word);
            }
        }
    }

    file.close();
    return ignoreWords;
}
