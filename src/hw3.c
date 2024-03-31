#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

#define MAX_SIZE 8

typedef struct {
    char board[MAX_SIZE][MAX_SIZE]; 
    int height[MAX_SIZE][MAX_SIZE];  
} GameState;

GameState* initialize_game_state(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    GameState *gameState = malloc(sizeof(GameState));
    if (!gameState) {
        perror("Failed to allocate memory for GameState");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            gameState->board[i][j] = '.';
            gameState->height[i][j] = 0; 
        }
    }

    char line[MAX_SIZE + 2]; 
    int row = 0;
    while (fgets(line, sizeof(line), file) && row < MAX_SIZE) {
        for (int col = 0; col < MAX_SIZE; col++) {
            if (line[col] == '.' || (line[col] >= 'A' && line[col] <= 'Z')) {
                gameState->board[row][col] = line[col];
                gameState->height[row][col] = (line[col] != '.') ? 1 : 0;
            }
        }
        row++;
    }

    fclose(file);
    return gameState;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;
    (void)num_tiles_placed;
    return NULL;
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
