#ifndef GUI_H
#define GUI_H


#include "../lib/raylib-cimgui/rlcimgui.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"
#include "types.h"
#include "consts.h"
// extern int grid[GRID_HEIGHT][GRID_WIDTH]; // Declare the grid array

void initImGUI();
void debug(struct World *world, bool *open);
void drawGUI(struct World *world, struct Input *inputs);
#endif // GUI_H
