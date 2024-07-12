#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "types.h"
#include "consts.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

void drawWire(World *world, struct Input *inputs, bool isPreview);
void drawGrid(World *world);
#endif // GRID_H
