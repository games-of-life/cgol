#ifndef GRID_H_
#define GRID_H_

typedef unsigned int uint;

/**
 * @brief Type for cell state
 * 
 */
typedef enum { dead = 0, alive = 1 } CellState;

/**
 * @brief Grid of the game: dimensions and contents of the field
 * 
 */
typedef struct {
    uint width;
    uint height;
    CellState *field;
} grid;

void grid_init(grid **gr, uint width, uint height);
CellState get(grid *gr, uint i, uint j);
void set(grid *gr, uint i, uint j, CellState val);
void grid_free(grid *gr);
void grid_noise(grid *gr, float prob);
void grid_cycle(grid *gr);
void grid_run_gol_step(grid *gr);

#endif