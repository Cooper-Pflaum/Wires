
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
  .menu_active = false,
  .offset = {0.0f, 0.0f},
  .zoom   = 5.0f,
};

struct Input inputs = {
  .color = RED,
  .type = 1,
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
}



int main(){
  init();

  
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D((Camera2D){.offset = {world.offset.x, world.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});
      drawGrid(&world);
      HandleInput(&world, &inputs);
    EndMode2D();


    GuiCheckBox((Rectangle) { 16, 16, 48, 48 }, "", &world.menu_active);

    DrawFPS(0,0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}




