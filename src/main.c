#include "grid.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

#define BOX_DIMENSION 2

int main(void) {
    srand(1);

    InitWindow(WIDTH, HEIGHT, "Game of life");

    SetTargetFPS(30);

    const uint box_width = WIDTH / BOX_DIMENSION;
    const uint box_height = HEIGHT / BOX_DIMENSION;

    grid *gr;

    grid_init(&gr, box_width, box_height);
    grid_noise(gr, 0.5);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < box_width; ++i) {
            for (int j = 0; j < box_height; ++j) {
                DrawRectangle(BOX_DIMENSION * i, BOX_DIMENSION * j,
                              BOX_DIMENSION - 1, BOX_DIMENSION - 1,
                              get(gr, i, j) ? WHITE : BLACK);
            }
        }
        grid_run_gol_step(gr);
        // break;
        // puts("another iteration");
        EndDrawing();
    }

    grid_free(gr);
    CloseWindow();
    return 0;
}
