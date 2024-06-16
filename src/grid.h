#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "../lib/types.h"
#include "../lib/consts.h"

extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

v2 SnapToGrid(v2 pos);
void drawWire(DrawingState *state, bool isPreview);
void drawGrid(DrawingState *state);

#endif // GRID_H
