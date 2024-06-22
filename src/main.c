
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
  .zoom   = 5.0f,
};

struct Input inputs = {
  .isDrawing = false,
  .drawHorizontalFirst = true,
  .directionSet = false,
};



int main(){
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(W, H, "Drawable Grid");
  int i = 0;
  for(int y = 0; y < GRID_WIDTH; y++){
    for(int x = 0; x < GRID_HEIGHT; x++){
      world.grid[i].state = 0;
      world.grid[i].color = BLACK;
      world.grid[i].pos = (v2) { (u16)(i%GRID_WIDTH) * CELL_SIZE, (u16)(i/GRID_HEIGHT) * CELL_SIZE};
      i++;
    }
  }

  world.grid[0].color = (Color){ 255, 0, 0, 255 };
  world.grid[1].color = (Color){ 0, 255, 0, 255 };
  world.grid[2].color = (Color){ 0, 0, 255, 255 };

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D((Camera2D){.offset = {world.offset.x, world.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});

      HandleInput(&world, &inputs);
      drawGrid(&world);
    EndMode2D();


    // Draw all squares in the grid

    //   if (drawing.isDrawing) {
    //     drawWire(&drawing, true, (Color){state.color.r, state.color.g, state.color.b, 100}); // Pass the state struct pointer and isPreview flag
    //   }

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
