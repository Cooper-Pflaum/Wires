#include <stdio.h>
#include <math.h>

#include "grid.h"
#include "input.h"
#include "../include/types.h"
#include "../include/consts.h"

#include "raylib.h"
#include "raymath.h"

#include "../lib/raylib-cimgui/rlcimgui.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

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

struct GUI {
  bool showMenu;
  bool showDemoWindow;
  ImVec4 clearColor;
};

void initGrid() {
  for(int i = 0; i < GRID_WIDTH; i++) {
    for(int j = 0; j < GRID_HEIGHT; j++) {
      world.grid[i].type = 0;
      world.grid[i].pos = (v2) { (u16)(i%GRID_WIDTH) * CELL_SIZE, (u16)(i/GRID_HEIGHT) * CELL_SIZE};
    }
  }
}

void initImGui() {
  igCreateContext(NULL);
  ImGuiIO *io = igGetIO();

  io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
  #ifdef IMGUI_HAS_DOCK
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
  #endif
  
  igStyleColorsDark(NULL);
  ImGui_ImplRaylib_Init();
  ImFontAtlas_AddFontDefault(io->Fonts, NULL);
  rligSetupFontAwesome();
  ImGui_ImplRaylib_BuildFontAtlas();
}

void drawGUI(struct GUI *gui) {
  igBegin("MENU", NULL, 0);
  igText("This is some useful text.");
  igCheckbox("Demo Window", &gui->showDemoWindow);
  igColorEdit3("Wire Color", (float*)&gui->clearColor, 0);
  igText("%.1f FPS (%.3f ms/frame)", igGetIO()->Framerate, 1000.0f / igGetIO()->Framerate);
  igEnd();
  if(gui->showDemoWindow) igShowDemoWindow(&gui->showDemoWindow);
}

int main() {
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(W, H, "Drawable Grid");

    initGrid();
    initImGui();

    struct GUI gui = {
        .showMenu = true,
        .showDemoWindow = false,
        .clearColor = {0.0f, 0.0f, 0.0f, 1.00f}
    };

    while (!WindowShouldClose()) {
      ImGui_ImplRaylib_ProcessEvents();
      ImGui_ImplRaylib_NewFrame();
      igNewFrame();

      // Raylib drawing begin
      BeginDrawing();
        ClearBackground((Color){0.0f, 0.0f, 0.0f, 1.0f});
        BeginMode2D((Camera2D){
          .offset = {world.offset.x, world.offset.y},
          .target = {0, 0},
          .rotation = 0.0f,
          .zoom = world.zoom
        });
        
        drawGrid(&world);
  
        bool isMouseOverImGuiWindow = igIsAnyItemHovered() || igIsWindowHovered(ImGuiHoveredFlags_AnyWindow);
        if(!isMouseOverImGuiWindow){
          HandleInput(&world, &inputs);
        }
        
        EndMode2D();

        drawGUI(&gui);

        igRender();
        ImGui_ImplRaylib_RenderDrawData(igGetDrawData());

      EndDrawing();
    }

    ImGui_ImplRaylib_Shutdown();
    igDestroyContext(NULL);
    CloseWindow();

    return 0;
}
