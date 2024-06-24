#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "../lib/types.h"
#include "../lib/consts.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

void drawWire(struct World *world, struct Input *inputs, bool isPreview);
void drawGrid(struct World *world);
#endif // GRID_H
