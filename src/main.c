
#include <stdio.h>
#include <math.h>

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
  .type = 0,
  .isDrawing = false,
  .direction = false,
  .directionSet = false,
};



void init(){
  SetTraceLogLevel(LOG_ERROR);
  // SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(W, H, "Drawable Grid");

  for(int i = 0; i < GRID_WIDTH; i++){
    for(int j = 0; j < GRID_HEIGHT; j++){
      world.grid[i].type = 0;
      world.grid[i].pos = (v2) { (u16)(i%GRID_WIDTH) * CELL_SIZE, (u16)(i/GRID_HEIGHT) * CELL_SIZE};
    }
  }

  world.grid[0].color = RED;
  world.grid[1].color = GREEN;
  world.grid[2].color = BLUE;

  world.grid[0].type = 1;
  world.grid[1].type = 1;
  world.grid[2].type = 1;
}



int main(){
  init();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);

    BeginMode2D((Camera2D){.offset = {world.offset.x, world.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});
      HandleInput(&world, &inputs);
      drawGrid(&world);
    EndMode2D();

    DrawFPS(0,0);
    char posText[32];
    sprintf(posText, "Pos: %.1f, %.1f", world.offset.x, world.offset.y);
    DrawText(posText, 0, 20, 20, GREEN);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}




