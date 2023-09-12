#ifndef GRID_H_
#define GRID_H_

#include <stdint.h>

typedef enum { Dead = 0, Alive = 1 } CellState;

typedef struct {
    uint64_t width;
    uint64_t height;
    CellState *field;
} grid;

void grid_init_random(grid **gr, uint64_t width, uint64_t height, float prob);
CellState get(grid *gr, uint64_t i, uint64_t j);
void set(grid *gr, uint64_t i, uint64_t j, CellState val);
void grid_free(grid *gr);
void grid_run_gol_step(grid *gr);

#endif
