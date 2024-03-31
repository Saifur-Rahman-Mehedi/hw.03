#ifndef HW3_H
#define HW3_H

#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 8

typedef struct {
    char board[MAX_SIZE][MAX_SIZE]; 
    int height[MAX_SIZE][MAX_SIZE];  
} GameState;

GameState* initialize_game_state(const char *filename);
GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed);
GameState* undo_place_tiles(GameState *game);
void free_game_state(GameState *game);
void save_game_state(GameState *game, const char *filename);

#endif // HW3_H
