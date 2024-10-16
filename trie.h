#ifndef HEADER_A7C0B97D41D176A4
#define HEADER_A7C0B97D41D176A4

/***************************************************************
# trie.h
# Header for trie.cpp, defines Trie class and TrieNode structure
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 16/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.10.0     15.10.2024   Initial implementation of Trie class
# 2024.10.1     16.10.2024   Added recursive destructor to free all nodes
****************************************************************/

#ifndef TRIE_H
#define TRIE_H

#include <string>
using namespace std;

// TrieNode class definition (this can also be a struct if you prefer)
class TrieNode
{
public:
    TrieNode* children[26];  // Pointers to child nodes for each alphabet letter
    bool isEndOfWord;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

// Trie class definition
class Trie
{
public:
    Trie();            // Constructor
    virtual ~Trie();   // Destructor

    void insert(const string& word);  // Insert word into Trie
    bool search(const string& word);  // Search for complete word in Trie
    bool startsWith(const string& prefix);  // Check if prefix exists in Trie

    TrieNode* root;  // Make the root public so it can be accessed by GridSearch

private:
    void clearTrie(TrieNode* node);  // Helper function for recursive node deletion
};

#endif // TRIE_H
#endif // header guard 

