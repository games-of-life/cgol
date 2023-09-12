#include "grid.h"
#include <stdlib.h>
#include <string.h>

void grid_init_random(grid **gr, uint64_t width, uint64_t height, float prob) {
    *gr = (grid *)malloc(sizeof(grid));
    (*gr)->width = width;
    (*gr)->height = height;
    (*gr)->field =
        (CellState *)malloc(sizeof(CellState) * (*gr)->width * (*gr)->height);
    for (uint64_t i = 0; i < width*height; ++i) {
        (*gr)->field[i] = ((rand() % 100) / 100. < prob) ? Alive : Dead;
    }
}

CellState get(grid *gr, uint64_t i, uint64_t j) {
    return gr->field[i * gr->height + j];
}

void set(grid *gr, uint64_t i, uint64_t j, CellState val) {
    gr->field[i * gr->height + j] = val;
}

void grid_free(grid *gr) {
    free(gr->field);
    free(gr);
}

uint64_t grid_calc_neighbors(grid *gr, uint64_t i, uint64_t j) {
    uint64_t count = 0;
    for (long i_cor = i - 1; i_cor <= i + 1; i_cor++) {
        for (long j_cor = j - 1; j_cor <= j + 1; j_cor++) {
            if (!((i_cor == i && j_cor == j) || (i_cor < 0 || j_cor < 0) ||
                  (i_cor >= gr->width || j_cor >= gr->height)) &&
                (Alive == get(gr, i_cor, j_cor))) {
                count++;
            }
        }
    }
    return count;
}

void grid_run_gol_step(grid *gr) {
    CellState *field_copy =
        (CellState *)malloc(sizeof(CellState) * gr->width * gr->height);

    for (uint64_t i = 0; i < gr->width; ++i) {
        for (uint64_t j = 0; j < gr->height; ++j) {
            uint64_t neigh = grid_calc_neighbors(gr, i, j);
            if ((3 == neigh) ||
                (2 == neigh && Alive == get(gr, i, j))) {
                field_copy[i * gr->height + j] = Alive;
            } else {
                field_copy[i * gr->height + j] = Dead;
            }
        }
    }

    free(gr->field);
    gr->field = field_copy;
}
