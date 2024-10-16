
# GridLex

GridLex is a lightning-fast word search tool designed for grids of letters. With its powerful Depth-First Search (DFS) algorithm and Trie-based word lookup, GridLex efficiently hunts down valid words in any direction—up, down, sideways, or diagonal. Perfect for word puzzle enthusiasts, game developers, or anyone working with word grids.

## Details

This repository contains a word search application that searches for words in a grid of characters. The application uses a depth-first search (DFS) algorithm and a Trie data structure to efficiently find words in the grid. The words are loaded from a CSV file, and the application supports ignoring specific words, removing spaces, fixing invalid values like NaN, and setting a minimum word length for valid words.

## Features

- **Depth-First Search (DFS):** Explore all possible directions in the grid to find words.
- **Trie Data Structure:** Efficient word lookup and prefix checking for valid words.
- **CSV Input:** Load the grid of characters and words from CSV files.
- **Ignore Words:** Support for specifying a set of words to ignore.
- **Minimum Word Length:** Option to define the minimum length of valid words.
- **NaN Handling:** Automatically skips invalid "NaN" values in CSV input.
- **Space Removal:** Removes spaces from the loaded words and ignore lists for cleaner processing.
- **Command-Line Switches:** Simplified options for input and program control.

## Files

- `gridsearch.cpp` - Contains the main logic for performing the word search using DFS.
- `gridsearch.h` - Header file for the grid search class.
- `trie.cpp` - Implements the Trie data structure for word lookups.
- `trie.h` - Header file for the Trie class.
- `main.cpp` - The main entry point of the application. Handles file input, output, and program switches.
- `README.md` - Project overview and instructions (this file).

## How It Works

1. **Grid Loading**: The grid is loaded from a CSV file, where each cell contains a single character. The grid is stored in a 2D vector.
2. **Word Loading**: The words are loaded from a separate CSV file into a Trie for fast lookup, ignoring NaN values and removing spaces.
3. **DFS Algorithm**: Starting from each cell in the grid, a DFS is performed in all 8 directions (up, down, left, right, and diagonals) to search for valid words in the Trie.
4. **Word Filtering**: Found words can be filtered by a minimum length, excluding words from an "ignore words" CSV file, and by removing spaces from the input.
5. **Error Handling**: Improved file error handling and NaN removal during CSV file parsing.

## Usage

### Command-line Arguments

The program expects the following command-line arguments:

```
./program <csv_grid_file> <csv_words_file> [options]
```

Options:
- `-i <csv_ignore_words_file>`: (Optional) A CSV file containing words to ignore.
- `-n <min_word_length>`: (Optional) The minimum length of words to consider (default: 3).
- `-h`: Display the help message.

### Example

Run the program with the grid file `grid.csv`, words file `words.csv`, ignore words file `ignore.csv`, and a minimum word length of 4:

```
./program grid.csv words.csv -i ignore.csv -n 4
```

### Help

To display usage instructions, run:

```
./program -h
```

## Compilation

You can compile the project using g++:

```bash
g++ -o program main.cpp gridsearch.cpp trie.cpp
```

## CSV Format

### Grid File (`grid.csv`)
The grid CSV file should contain a rectangular grid of characters where each row is a line in the CSV:

```
A,B,C,D
E,F,G,H
I,J,K,L
M,N,O,P
```

### Words File (`words.csv`)
The words CSV file should contain a list of valid words to search for. NaN values and spaces are automatically cleaned:

```
APPLE,ORANGE,BANANA,PEAR
```

### Ignore Words File (`ignore.csv`)
The ignore words CSV file should contain a list of words to ignore during the search. Spaces and NaN values are removed:

```
A,AN,THE,IS
```

## License

This project is open source and available under the [MIT License](LICENSE).

## Contributions

Feel free to submit pull requests or issues. Contributions are welcome!
