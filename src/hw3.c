#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

bool isWordInDictionary(const char* word);
bool isConnected(GameState *game, int row, int col, char direction, const char *tiles);

bool isValidPlacement(GameState *game, int row, int col, char direction, const char *tiles) {

    int length = strlen(tiles);
    if (direction == 'H' && (col + length > game->numCols)) return false;
    if (direction == 'V' && (row + length > game->numRows)) return false;

    char word[MAX_SIZE * 2]; 
    int wordIndex = 0;

    for (int i = 0; i < length; ++i) {
        int currentRow = direction == 'V' ? row + i : row;
        int currentCol = direction == 'H' ? col + i : col;
        
        if (tiles[i] == ' ') {
            if (game->board[currentRow][currentCol] == '.') {
                return false; 
            }
            word[wordIndex++] = game->board[currentRow][currentCol];
        } else {
            if (game->height[currentRow][currentCol] >= 5) {
                return false; 
            }
            word[wordIndex++] = tiles[i];
        }
    }
    word[wordIndex] = '\0'; 

    if (!isWordInDictionary(word)) {
        return false;
    }

    if (!isConnected(game, row, col, direction, tiles)) {
        return false;
    }

    return true; 
}

void initializeBoard(GameState *game, int rows, int cols) {
    game->board = (char **)malloc(rows * sizeof(char *));
    game->height = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        game->board[i] = (char *)calloc(cols, sizeof(char));
        game->height[i] = (int *)calloc(cols, sizeof(int));
        for (int j = 0; j < cols; ++j) {
            game->board[i][j] = '.';
        }
    }
    game->numRows = rows;
    game->numCols = cols;
}

void resizeBoardIfNeeded(GameState *game, int newRowSize, int newColSize) {

    if (newRowSize > game->numRows) {
        game->board = (char **)realloc(game->board, newRowSize * sizeof(char *));
        game->height = (int **)realloc(game->height, newRowSize * sizeof(int *));
        for (int i = game->numRows; i < newRowSize; ++i) {
            game->board[i] = (char *)calloc(newColSize, sizeof(char));
            game->height[i] = (int *)calloc(newColSize, sizeof(int));
            for (int j = 0; j < newColSize; ++j) {
                game->board[i][j] = '.';
            }
        }
    }

    for (int i = 0; i < game->numRows; ++i) {
        if (newColSize > game->numCols) {
            game->board[i] = (char *)realloc(game->board[i], newColSize * sizeof(char));
            game->height[i] = (int *)realloc(game->height[i], newColSize * sizeof(int));
            for (int j = game->numCols; j < newColSize; ++j) {
                game->board[i][j] = '.';
                game->height[i][j] = 0;
            }
        }
    }
    game->numRows = newRowSize > game->numRows ? newRowSize : game->numRows;
    game->numCols = newColSize > game->numCols ? newColSize : game->numCols;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    if (!isValidPlacement(game, row, col, direction, tiles)) {
        return game; 
    }

    int length = strlen(tiles);
    *num_tiles_placed = 0;

    for (int i = 0; i < length; ++i) {
        int currentRow = direction == 'V' ? row + i : row;
        int currentCol = direction == 'H' ? col + i : col;

    if (currentRow >= MAX_SIZE || currentCol >= MAX_SIZE) {
        resizeBoardIfNeeded(game, currentRow + 1, currentCol + 1);
    }

        if (tiles[i] != ' ') { 
            game->board[currentRow][currentCol] = tiles[i];
            game->height[currentRow][currentCol]++;
            (*num_tiles_placed)++;
        }
    }

    return game;
}



GameState* undo_place_tiles(GameState *game) {
    (void)game;
    return NULL;
}

void free_game_state(GameState *game) {
    (void)game;
}

void save_game_state(GameState *game, const char *filename) {
    (void)game;
    (void)filename;
}
