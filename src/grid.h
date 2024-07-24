#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "types.h"
#include "consts.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

void drawWire(World *world, struct Input *inputs, bool isPreview);
void drawWireConnections(World *world, u16 x, u16 y, Color color);
bool isIntersection(World *world, u16 x, u16 y);
void drawIntersection(World *world, u16 x, u16 y);
bool ColorEquals(Color c1, Color c2);
void drawGrid(World *world);
void drawWireCell(World *world, u16 x, u16 y);
void connectAdjacentCells(World *world, u16 x, u16 y, Rectangle cellRect, Color color);

#endif // GRID_H
