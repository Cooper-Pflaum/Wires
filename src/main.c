
#include <stdio.h>
#include "grid.h"
#include "input.h"
#include "../lib/types.h"
#include "../lib/consts.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raylibs/raygui.h"
#include "../lib/raylibs/raymath.h"
#include "raylib.h"


DrawingState state = {
    .startPos = {0, 0},
    .endPos = {0, 0},
    .isDrawing = false,
    .drawHorizontalFirst = true,
    .directionSet = false,
    .zoom = 1.0f,
    .offset = {0.0f, 0.0f}
  };


int main() {
  SetTraceLogLevel(LOG_ERROR);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(W, H, "Drawable Grid");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D((Camera2D){.offset = {state.offset.x, state.offset.y}, .target = {0, 0}, .rotation = 0.0f, .zoom = state.zoom});

    HandleInput(&state);

    if (state.isDrawing) {
      drawWire(&state, true); // Pass the state struct pointer and isPreview flag
    }

    drawGrid(&state); // Pass the state struct pointer
    GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
                    "#191#Message Box", "Hi! This is a message!", "Nice;Cool");
    EndMode2D();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
