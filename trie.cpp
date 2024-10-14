#include "trie.h"

// Constructor to initialize the root node of the Trie
Trie::Trie() {
    root = new TrieNode();
}

// Destructor to clean up dynamically allocated memory (TrieNodes)
Trie::~Trie() {
    // You may want to write a recursive function to free all nodes
}

// Insert a word into the Trie
void Trie::insert(const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        // Check if the character is an alphabetic letter
        if (isalpha(c)) {
            int index = toupper(c) - 'A';  // Convert to uppercase and get index in range 0-25
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        } else {
            // Skip non-alphabetic characters
            continue;
        }
    }
    node->isEndOfWord = true;
}


// Search for a complete word in the Trie
bool Trie::search(const string& word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return false;  // Word not found
        }
        node = node->children[index];
    }
    return node != nullptr && node->isEndOfWord;  // True if end of word is reached
}

// Search for a prefix in the Trie
bool Trie::startsWith(const string& prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (node->children[index] == nullptr) {
            return false;  // Prefix not found
        }
        node = node->children[index];
    }
    return node != nullptr;  // True if prefix is found
}
