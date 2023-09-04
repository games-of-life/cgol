#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocate memory for the grid, Set Width and Height. Each cell is allovated according to prob
 *
 * @param gr Grid pointer
 * @param width Width of the grid
 * @param height Height of the grid
 * @param prob Probability of a cell being alive
 */
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

/**
 * @brief Get the state of a cell in grid gr at coordinates i, j
 *
 * @param gr Grid to get coords out of
 * @param i x coordinate
 * @param j y coordinate
 * @return CellState State of the cell at i, j in grid
 */
CellState get(grid *gr, uint i, uint j) {
    return gr->field[i * gr->height + j];
}

/**
 * @brief Set the state of a cell in grid at coordinates i, j
 *
 * @param gr Grid to get coords out of
 * @param i x coordinate
 * @param j y coordinate
 * @param val CellState to set cell to
 */
void set(grid *gr, uint i, uint j, CellState val) {
    gr->field[i * gr->height + j] = val;
}

/**
 * @brief Free the memory allocated for grid gr.
 *
 * @param gr grid to free
 */
void grid_free(grid *gr) {
    free(gr->field);
    free(gr);
}

/**
 * @brief Calculate amount of alive neighbors of a cell in grid C
 *
 * @param gr Grid to calculate neighbors in
 * @param i x coordinate
 * @param j y coordinate
 * @return uint Amount of neighbors of point at coordinates i, j
 */
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

/**
 * @brief Progress Game Of Life
 *
 * @param gr Grid to have game processed in
 */
void grid_run_gol_step(grid *gr) {
    CellState *field_copy =
        (CellState *)malloc(sizeof(CellState) * gr->width * gr->height);

    for (uint i = 0; i < gr->width; ++i) {
        for (uint j = 0; j < gr->height; ++j) {
            uint neigh = grid_calc_neighbors(gr, i, j);
            if ((alive == get(gr, i, j) && (2 == neigh || 3 == neigh)) ||
                (dead == get(gr, i, j) && 3 == neigh)) {
                field_copy[i * gr->height + j] = alive;
            } else {
                field_copy[i * gr->height + j] = dead;
            }
        }
    }

    free(gr->field);
    gr->field = field_copy;
}