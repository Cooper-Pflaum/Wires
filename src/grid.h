#ifndef GRID_H
#define GRID_H

#include "raylib.h"

#define GRID_WIDTH 1000
#define GRID_HEIGHT 1000
#define CELL_SIZE 30

typedef Vector2 v2;

extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

v2 SnapToGrid(Vector2 pos);
void drawWire(v2 startPos, v2 endPos, bool drawHorizontalFirst, bool isPreview);
void drawGrid(float zoom, Vector2 offset); // Add the prototype for DrawGrid

#endif // GRID_H
