#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grid_init_random(grid **gr, uint width, uint height, float prob) {
    *gr = (grid *)malloc(sizeof(grid));
    (*gr)->width = width;
    (*gr)->height = height;
    (*gr)->field =
        (CellState *)malloc(sizeof(CellState) * (*gr)->width * (*gr)->height);
    for (uint i = 0; i < width*height; ++i) {
        (*gr)->field[i] = ((rand() % 100) / 100. < prob) ? alive : dead;
    }
}

CellState get(grid *gr, uint i, uint j) {
    return gr->field[i * gr->height + j];
}

void set(grid *gr, uint i, uint j, CellState val) {
    gr->field[i * gr->height + j] = val;
}

void grid_free(grid *gr) {
    free(gr->field);
    free(gr);
}

uint grid_calc_neighbors(grid *gr, uint i, uint j) {
    uint count = 0;
    for (long i_cor = i - 1; i_cor <= i + 1; i_cor++) {
        for (long j_cor = j - 1; j_cor <= j + 1; j_cor++) {
            if (!((i_cor == i && j_cor == j) || (i_cor < 0 || j_cor < 0) ||
                  (i_cor >= gr->width || j_cor >= gr->height)) &&
                (alive == get(gr, i_cor, j_cor))) {
                count++;
            }
        }
    }
    return count;
}

void grid_run_gol_step(grid *gr) {
    CellState *field_copy =
        (CellState *)malloc(sizeof(CellState) * gr->width * gr->height);

    for (uint i = 0; i < gr->width; ++i) {
        for (uint j = 0; j < gr->height; ++j) {
            uint neigh = grid_calc_neighbors(gr, i, j);
            if ((3 == neigh) ||
                (2 == neigh && alive == get(gr, i, j))) {
                field_copy[i * gr->height + j] = alive;
            } else {
                field_copy[i * gr->height + j] = dead;
            }
        }
    }

    free(gr->field);
    gr->field = field_copy;
}
