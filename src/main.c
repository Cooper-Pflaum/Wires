
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
  .zoom   = 3.0f,
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
  // SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(W, H, "Drawable Grid");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // BeginMode2D((Camera2D){.offset = {world.offset.x + MENU_OFFSET, world.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = world.zoom});
    //   HandleInput(&drawing);
    //   if (drawing.isDrawing) {
    //     drawWire(&drawing, true, (Color){state.color.r, state.color.g, state.color.b, 100}); // Pass the state struct pointer and isPreview flag
    //   }
    //   drawGrid(&drawing); // Pass the state struct pointer
    // EndMode2D();

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
