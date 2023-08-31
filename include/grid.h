#ifndef GRID_H_
#define GRID_H_

typedef unsigned int uint;

typedef struct {
    uint width;
    uint height;
    uint *field;
} grid;

enum CellState {
    dead = 0,
    alive = 1
};

void grid_init(grid **gr, uint width, uint height);
int get(grid *gr, uint i, uint j);
void set(grid *gr, uint i, uint j, uint val);
void grid_free(grid *gr);
void grid_noise(grid *gr, float prob);
void grid_cycle(grid *gr);
void grid_run_gol_step(grid *gr);

#endif