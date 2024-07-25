#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "types.h"
#include "consts.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array
CellArray initCellArray();
void freeCellArray(CellArray* cellArray);

void updateGridCell(CellArray *cellArray, u32 x, u32 y, cellType type, Color color);
void drawWire(World *world, Input *inputs, bool isPreview);
void drawGrid(World *world);

#endif // GRID_H
