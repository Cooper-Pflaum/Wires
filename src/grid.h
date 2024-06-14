#ifndef GRID_H
#define GRID_H


#define GRID_WIDTH 500
#define GRID_HEIGHT 500
#define CELL_SIZE 20



#include "raylib.h"
typedef Vector2 v2;

extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

v2 SnapToGrid(Vector2 pos);
void drawWire(v2 startPos, v2 endPos, bool drawHorizontalFirst, bool isPreview);
void drawGrid(float zoom, Vector2 offset); // Add the prototype for DrawGrid

#endif // GRID_H
