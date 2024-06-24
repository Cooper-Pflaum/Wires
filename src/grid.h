#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "../lib/types.h"
#include "../lib/consts.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

// void drawWire(DrawingState *state, bool isPreview, Color wire_color);
// void drawGrid(DrawingState *state);

void drawGrid(struct World *world);
#endif // GRID_H
