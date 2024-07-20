#include "raylib.h"
#include "../lib/raylib-cimgui/rlcimgui.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"
#include "types.h"
#include "consts.h"
#include "utils.h"

void initImGUI(){
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

void debug(World *world, struct Input *inputs, bool *open) {
  if (!*open) return;
  
  static bool vsync_enabled = true;

  igBegin("Debug", open, 0);    
  igSeparatorText("System Info");
  igText("%.1f FPS (%.1f ms)", igGetIO()->Framerate, 1000.0f / igGetIO()->Framerate);
  if (igCheckbox("VSync", &vsync_enabled)) {
    vsync_enabled ? SetWindowState(FLAG_VSYNC_HINT) : ClearWindowState(FLAG_VSYNC_HINT);
  }

  igSeparatorText("World Info");
  igText("Zoom: %.2f", world->zoom);
  igText("Grid Size: %dx%d", GRID_WIDTH, GRID_HEIGHT);
  igText("World Offset: (%.2f, %.2f)", world->offset.x, world->offset.y);

  igSeparatorText("Input Info");

  v2 mousePos = GetMousePosition();
  igText("Mouse Grid Pos: (%d, %d)", 
         (u32)((mousePos.x - world->offset.x) / (CELL_SIZE * world->zoom)), 
         (u32)((mousePos.y - world->offset.y) / (CELL_SIZE * world->zoom))
  );

  // igText("Start Pos: (%d, %d)", inputs->startPos.x, inputs->startPos.y);
  // igText("End Pos: (%d, %d)", inputs->endPos.x, inputs->endPos.y);
  igText("Wire Type: %d", inputs->type);
  igText("Wire Color: (%d, %d, %d)", inputs->wire_color.r, inputs->wire_color.g, inputs->wire_color.b);
  igText("Wire Direction: %s", inputs->direction ? "Horizontal First" : "Vertical First");

  igSeparatorText("Game State");
  // igText("Placed Components: %d", world->componentCount);
  // igText("Game State: %s", GetGameStateString(world->gameState));
  // igText("Selected Tool: %s", GetToolString(inputs->currentTool));
  igEnd();
}

void drawGUI(World *world, struct Input *inputs) {
  GUI *gui = &world->gui;

  igBegin("MENU", NULL, 0);
  igSeparatorText("Wire Select");

  // Color dropdown menu
  const char* color_items[] = { "Red", "Green", "Blue", "Yellow", "Cyan", "Magenta", "White" };
  const Color color_values[] = {
    RED, GREEN, BLUE, YELLOW, SKYBLUE, MAGENTA, WHITE 
  };
  static int color_item_current = 0;

  if (igBeginCombo("Wire Color", color_items[color_item_current], 0)) {
    for (u8 n = 0; n < (u8)(sizeof(color_items) / sizeof(color_items[0])); n++) {
      bool is_selected = (color_item_current == n);
      
      // Display color box
      ImVec4 imcolor = ColorToImVec4(color_values[n]);
      igColorButton("##color", imcolor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, (ImVec2){20, 20});
      igSameLine(0, 5);

      if (igSelectable_Bool(color_items[n], is_selected, 0, (ImVec2){0,0})) {
        color_item_current = n;
        inputs->wire_color = color_values[n];
      }
      if (is_selected) {
        igSetItemDefaultFocus();
      }
    }
    igEndCombo();
  }

  // Display current color box outside the dropdown
  ImVec4 current_imcolor = ColorToImVec4(inputs->wire_color);
  igColorButton("##current_color", current_imcolor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, (ImVec2){20, 20});
  igSameLine(0, 5);
  igText("Current Color");

  igCheckbox("Debug", &gui->show_debug);
  igEnd();

  // Call debug function outside of the main menu window
  debug(world, inputs, &gui->show_debug);
  igRender();
  ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
}
