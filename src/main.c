#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "../lib/raylib/raymath.h"
#include "gui.h"

#include "grid.h"
#include "input.h"
#include "types.h"
#include "consts.h"

World world = {
  .menu_active = false,
  .offset = {0.0f, 0.0f},
  .zoom   = 5.0f,


    // Initialize GUI struct
  .gui = (GUI){
      .show_debug = false,
      .selected_bits = 1,
      .wire_color = RED,  // Default color
      .show_bits_popup = false
  },
};

struct Input inputs = {
  .color = RED,
  .type = 1,
  .isDrawing = false,
  .direction = false,
  .directionSet = false,
};

void init(){
  // Init Raylib
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(W, H, "Drawable Grid");
  initImGUI();

  // Init grid
  for(int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
    world.grid[i].type = 0;
    world.grid[i].pos = (v2){(u16)(i % GRID_WIDTH) * CELL_SIZE, (u16)(i / GRID_WIDTH) * CELL_SIZE};
  }
}

void update(){
  ImGui_ImplRaylib_ProcessEvents();
  ImGui_ImplRaylib_NewFrame();
  igNewFrame();

  if(!(igIsAnyItemHovered() || igIsWindowHovered(ImGuiHoveredFlags_AnyWindow))){
    HandleInput(&world, &inputs);
  }
  else {
    inputs.isDrawing = false;
  }
}

void render(){
  // Raylib  
  ClearBackground((Color){0.0f, 0.0f, 0.0f, 1.0f});
  BeginDrawing();
    BeginMode2D((Camera2D){ .offset = world.offset, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});  
      drawGrid(&world);
    EndMode2D();
  drawGUI(&world, &inputs);
  EndDrawing();
}


int main() {
  init();
  while (!WindowShouldClose()) {
    update();
    render();
  }
  // Close ImGUI and Raylib
  ImGui_ImplRaylib_Shutdown();
  igDestroyContext(NULL);
  CloseWindow();
  return 0;
}
