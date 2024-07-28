#include <stdio.h>
#include "raylib.h"

#include "gui.h"
#include "render.h"
#include "input.h"
#include "types.h"
#include "consts.h"

World world = {
    .menu_active = false,
    .offset = { 0.0f, 0.0f },
    .zoom   = 5.0f,
    .screenSize = { .x=W, .y=H },
    .gui = {
      .show_debug = false,
      .show_debug_lines = false,
      .selected_bits = 1,
      .wire_color = RED,  // Default color
      .show_bits_popup = false
    },
    .grid = {0},  // Initialize to zero, we'll properly initialize it later
};

Input inputs = {
    .wire_color = RED,
    .type = 1,
    .isDrawing = false,
    .direction = false,
    .directionSet = false,
};

void init() {
    // Init Raylib
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(W, H, "Drawable Grid");
    initImGUI();

    // Init grid
    world.grid = initCellArray();
}

void update() {
    ImGui_ImplRaylib_ProcessEvents();
    ImGui_ImplRaylib_NewFrame();
    igNewFrame();

    if (!(igIsAnyItemHovered() || igIsWindowHovered(ImGuiHoveredFlags_AnyWindow))) {
        HandleInput(&world, &inputs);
    } else {
        inputs.isDrawing = false;
    }
    if (IsWindowResized()) world.screenSize = (v2) {GetScreenWidth(), GetScreenHeight()};
}


int main() {
    init();
    while (!WindowShouldClose()) {
      update();
      render(&world, &inputs);
    }
    // Close ImGUI and Raylib
    ImGui_ImplRaylib_Shutdown();
    igDestroyContext(NULL);
    CloseWindow();
    
    // Free the allocated memory for the grid
    freeCellArray(&world.grid);
    
    return 0;
}
