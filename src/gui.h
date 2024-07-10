#ifndef GRID_H
#define GRID_H


#include "../include/types.h"
#include "../include/consts.h"
#include "../lib/raylib-cimgui/rlcimgui.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

void drawWire(struct World *world, struct Input *inputs, bool isPreview);
void drawGrid(struct World *world);
#endif // GRID_H
