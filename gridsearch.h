#ifndef GRIDSEARCH_H
#define GRIDSEARCH_H

#include <vector>
#include <string>
#include <set>
#include "trie.h"

class GridSearch {
public:
    GridSearch();
    ~GridSearch();

    // Depth-first search (DFS) to find words in the grid
    void dfs(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, TrieNode* node, int x, int y, std::string word, std::vector<std::string>& result, std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& locations, std::set<std::string>& foundWords, const std::set<std::string>& ignoreWords, int minWordLength, int startX, int startY, int dirX, int dirY);

    // Search for words in the grid
    std::vector<std::string> searchWords(std::vector<std::vector<char>>& grid, Trie* trie, std::vector<std::pair<std::string, std::pair<std::pair<int, int>, std::pair<int, int>>>>& locations, const std::set<std::string>& ignoreWords, int minWordLength);
};

// Functions to read from CSV files
std::vector<std::vector<char>> readCSVFile(const std::string& filename);
void loadWordsFromCSVFile(const std::string& filename, Trie& trie);
std::set<std::string> loadIgnoreWordsFromCSV(const std::string& filename);

#endif // GRIDSEARCH_H
