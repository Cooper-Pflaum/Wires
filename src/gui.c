
#include "../lib/raylib-cimgui/rlcimgui.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"
#include "types.h"
#include "consts.h"



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
  u32 gridX = (int)((mousePos.x - world->offset.x) / (CELL_SIZE * world->zoom));
  u32 gridY = (int)((mousePos.y - world->offset.y) / (CELL_SIZE * world->zoom));
  igText("Mouse Grid Pos: (%d, %d)", gridX, gridY);
  // igText("Start Pos: (%d, %d)", inputs->startPos.x, inputs->startPos.y);
  // igText("End Pos: (%d, %d)", inputs->endPos.x, inputs->endPos.y);
  igText("Wire Type: %d", inputs->type);
  igText("Wire Color: (%d, %d, %d)", inputs->color.r, inputs->color.g, inputs->color.b);
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

  if (igButton("Data bits", (ImVec2){0,0})) {
    gui->show_bits_popup = true;
  }

  if (gui->show_bits_popup) {
    igOpenPopup_Str("bits_popup", 0);
    gui->show_bits_popup = false;
  }

  if (igBeginPopup("bits_popup", 0)) {
    for (int bits = 1; bits <= 64; bits *= 2)
      if (igSelectable_Bool(TextFormat("%d bits", bits), gui->selected_bits == bits, 0, (ImVec2){0,0}))
        gui->selected_bits = bits;
    igEndPopup();
  }
  igSameLine(0, -1);
  igText("%d bits", gui->selected_bits);

  f32 color[4] = {gui->wire_color.r / 255.0f, gui->wire_color.g / 255.0f, gui->wire_color.b / 255.0f, 1.0f};
  if (igColorEdit4("Wire Color", color, ImGuiColorEditFlags_NoAlpha)) {
    gui->wire_color = (Color){(u8)(color[0] * 255), (u8)(color[1] * 255), (u8)(color[2] * 255), 255};
  }

  igCheckbox("Debug", &gui->show_debug);

  igEnd();

  // Call debug function outside of the main menu window
  debug(world, inputs, &gui->show_debug);

  igRender();
  ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
}
