/***************************************************************
# trie.cpp
# Code implementing Trie data structure for efficient word lookups
# Copyright (C) 2024 C. Brown (dev@coralesoft.nz)
# This software is released under the MIT License.
# See the LICENSE file in the project root for the full license text.
# Last revised 16/10/2024
#-----------------------------------------------------------------------
# Version      Date         Notes:
# 2024.10.0     15.10.2024   Initial implementation of Trie class
# 2024.10.1     16.10.2024   Added recursive destructor to free all nodes,
#                           fixed case-sensitivity in search and startsWith.
****************************************************************/

#include "trie.h"
#include <cctype>  // For toupper

// Constructor to initialize the root node of the Trie
Trie::Trie()
{
    root = new TrieNode();
}

// Destructor to clean up dynamically allocated memory (TrieNodes)
Trie::~Trie()
{
    clearTrie(root);  // Call a recursive function to delete nodes
}

// Recursive function to delete all nodes in the Trie
void Trie::clearTrie(TrieNode* node)
{
    if (node == nullptr) return;
    for (int i = 0; i < 26; ++i)
    {
        clearTrie(node->children[i]);  // Recursively delete children
    }
    delete node;  // Delete the current node
}

// Insert a word into the Trie
void Trie::insert(const string& word)
{
    TrieNode* node = root;
    for (char c : word)
    {
        // Check if the character is an alphabetic letter
        if (isalpha(c))
        {
            int index = toupper(c) - 'A';  // Convert to uppercase and get index in range 0-25
            if (node->children[index] == nullptr)
            {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        else
        {
            // Skip non-alphabetic characters
            continue;
        }
    }
    node->isEndOfWord = true;
}

// Search for a complete word in the Trie
bool Trie::search(const string& word)
{
    TrieNode* node = root;
    for (char c : word)
    {
        if (!isalpha(c)) continue;  // Skip non-alphabetic characters
        int index = toupper(c) - 'A';  // Convert to uppercase
        if (index < 0 || index >= 26 || node->children[index] == nullptr)
        {
            return false;  // Word not found
        }
        node = node->children[index];
    }
    return node != nullptr && node->isEndOfWord;  // True if end of word is reached
}

// Search for a prefix in the Trie
bool Trie::startsWith(const string& prefix)
{
    TrieNode* node = root;
    for (char c : prefix)
    {
        if (!isalpha(c)) continue;  // Skip non-alphabetic characters
        int index = toupper(c) - 'A';  // Convert to uppercase
        if (index < 0 || index >= 26 || node->children[index] == nullptr)
        {
            return false;  // Prefix not found
        }
        node = node->children[index];
    }
    return node != nullptr;  // True if prefix is found
}
