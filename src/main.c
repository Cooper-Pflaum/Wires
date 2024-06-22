
#include <stdio.h>
#include "grid.h"
#include "input.h"
#include "../lib/types.h"
#include "../lib/consts.h"

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "../lib/raylibs/raygui.h"
#include "../lib/raylibs/raymath.h"


struct World world = {
  .offset = {0.0f, 0.0f},
  .zoom   = 10.0f,
};

struct Drawing drawing = {
  .startPos = {0, 0},
  .endPos = {0, 0},
  .isDrawing = false,
  .drawHorizontalFirst = true,
  .directionSet = false,
};




int main() {
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(W, H, "Drawable Grid");


  for(int i = 0; i < GRID_WIDTH*GRID_HEIGHT; i++){
    world.grid[i].state = 0;
    world.grid[i].color = (Color){255 * (i/256), 255 * (i/256), 255 * (i/256), 255};
    world.grid[i].pos = (v2) { (int)(i/GRID_WIDTH) * CELL_SIZE, (int)(i%GRID_HEIGHT) * CELL_SIZE};
  }


  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    

    BeginMode2D((Camera2D){.offset = {world.offset.x, world.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});


    // Draw all squares in the grid
    // for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
    //   DrawRectangle(world.grid[i].pos.x, world.grid[i].pos.y, CELL_SIZE, CELL_SIZE, world.grid[i].color);
    // }
    //   HandleInput(&drawing);
    //   if (drawing.isDrawing) {
    //     drawWire(&drawing, true, (Color){state.color.r, state.color.g, state.color.b, 100}); // Pass the state struct pointer and isPreview flag
    //   }
      drawGrid(&world); // Pass the state struct pointer
    EndMode2D();

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
