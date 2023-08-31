#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grid_init(grid **gr, uint width, uint height) {
    *gr = (grid *)malloc(sizeof(grid));
    (*gr)->width = width;
    (*gr)->height = height;
    (*gr)->field = (uint *)malloc(sizeof(uint) * (*gr)->width * (*gr)->height);
}

int get(grid *gr, uint i, uint j) { return gr->field[i * gr->height + j]; }

void set(grid *gr, uint i, uint j, uint val) {
    gr->field[i * gr->height + j] = val;
}

void grid_free(grid *gr) { free(gr); }

void grid_noise(grid *gr, float prob) {
    for (uint i = 0; i < gr->width; ++i) {
        for (uint j = 0; j < gr->height; ++j) {
            if ((rand() % 100) / 100. < prob) {
                set(gr, i, j, alive);
            } else {
                set(gr, i, j, dead);
            }
        }
    }
}

void grid_cycle(grid *gr) {
    memset(gr->field, dead, gr->width * gr->height);
    uint x = gr->width / 2, y = gr->height / 2;
    printf("%d %d\n", x, y);
    set(gr, x, y, alive);
    set(gr, x + 1, y, alive);
    set(gr, x - 1, y, alive);
    // set(gr, x + 1, y, alive);
    // set(gr, x + 1, y + 1, alive);
}

int grid_calc_neighbors(grid *gr, int i, int j) {
    int i_cor, j_cor, count = 0;
    for (i_cor = i - 1; i_cor <= i + 1; i_cor++) {
        for (j_cor = j - 1; j_cor <= j + 1; j_cor++) {
            if ((i_cor == i && j_cor == j) || (i_cor < 0 || j_cor < 0) ||
                (i_cor >= gr->width || j_cor >= gr->height)) {
                continue;
            }
            if (get(gr, i_cor, j_cor) == alive) {
                count++;
            }
        }
    }
    return count;
}

void grid_run_gol_step(grid *gr) {
    uint *field_copy = (uint *)malloc(sizeof(uint) * gr->width * gr->height);
    for (uint i = 0; i < gr->width; ++i) {
        for (uint j = 0; j < gr->height; ++j) {
            int neigh = grid_calc_neighbors(gr, i, j);
            if (get(gr, i, j) == alive && (neigh == 2 || neigh == 3)) {
                field_copy[i * gr->height + j] = alive;
            } else if (get(gr, i, j) == dead && neigh == 3) {
                field_copy[i * gr->height + j] = alive;
            } else {
                field_copy[i * gr->height + j] = dead;
            }
        }
    }
    free(gr->field);
    gr->field = field_copy;
}