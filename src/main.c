#include <stdio.h>
#include <math.h>

#include "grid.h"
#include "input.h"
#include "types.h"
#include "consts.h"

#include "raylib.h"
#include "../lib/raylib/raymath.h"


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

void drawGUI(struct GUI *gui, struct Input *inputs) {


  igBegin("MENU", NULL, 0);
  igSeparatorText("Wire Select");
  // igInputInt("Data Bits", &bits, 1, 100, 0);
  
  // Declare this at file scope or as a static variable in your rendering function
static int selected_bits = 8; // Default value

if (igButton("Data bits", (ImVec2){0,0})) {
    igOpenPopup_Str("bits_popup", 0);
}
igSameLine(0, -1);
igText("%d bits", selected_bits);

if (igBeginPopup("bits_popup", 0)) {
    for (int bits = 1; bits <= 64; bits *= 2)
        if (igSelectable_Bool(TextFormat("%d bits", bits), selected_bits == bits, 0, (ImVec2){0,0}))
            selected_bits = bits;
    igEndPopup();
}

  // Convert Color to float array
  float color[4] = {
    inputs->color.r / 255.0f,
    inputs->color.g / 255.0f,
    inputs->color.b / 255.0f,
    inputs->color.a / 255.0f
  };
  
  if (igColorEdit4("Wire Color", color, ImGuiColorEditFlags_NoAlpha)) {
    // Convert back to Color if changed
    inputs->color = (Color){
      (unsigned char)(color[0] * 255),
      (unsigned char)(color[1] * 255),
      (unsigned char)(color[2] * 255),
      255
    };
  }

ImVec2 window_size;
igGetWindowSize(&window_size);

ImVec2 text_size;
igCalcTextSize(&text_size, "000.0 FPS (00.0 ms)", NULL, false, -1.0f);

igSetCursorPos((ImVec2){
    window_size.x - text_size.x - 10.0f,
    20.0f
});
igText("%.1f FPS (%.1f ms)", igGetIO()->Framerate, 1000.0f / igGetIO()->Framerate);
  // igCheckbox("Demo Window", &gui->showDemoWindow);
  // if(gui->showDemoWindow) igShowDemoWindow(&gui->showDemoWindow);
  igEnd();
}

int main() {
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
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
  
        if(!(igIsAnyItemHovered() || igIsWindowHovered(ImGuiHoveredFlags_AnyWindow))){
          HandleInput(&world, &inputs);
        }
        
        EndMode2D();

        drawGUI(&gui, &inputs);

        igRender();
        ImGui_ImplRaylib_RenderDrawData(igGetDrawData());

      EndDrawing();
    }

    ImGui_ImplRaylib_Shutdown();
    igDestroyContext(NULL);
    CloseWindow();

    return 0;
}
