
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


void debug(struct World *world, bool *open) {
  if (!*open) return;
  
  static bool vsync_enabled = true;  // VSync enabled by default


  igBegin("Debug", open, 0);
  igSeparatorText("Debug");
    // VSync toggle
  if (igCheckbox("VSync", &vsync_enabled)) {
    if (vsync_enabled) {
      SetWindowState(FLAG_VSYNC_HINT);
    } else {
      ClearWindowState(FLAG_VSYNC_HINT);
    }
  }
  igText("Zoom: %0.1f", world->zoom);
  // Mouse position in grid coordinates
  v2 mousePos = GetMousePosition();
  u32 gridX = (int)((mousePos.x - world->offset.x) / (CELL_SIZE * world->zoom));
  u32 gridY = (int)((mousePos.y - world->offset.y) / (CELL_SIZE * world->zoom));
  igText("Mouse Grid Pos:\n      (%d, %d)", gridX, gridY);
  igText("%.1f FPS (%.1f ms)", igGetIO()->Framerate, 1000.0f / igGetIO()->Framerate);
  
  igEnd();
}

void drawGUI(struct World *world, struct Input *inputs) {
  static bool show_debug = true;
  static u8 selected_bits = 1; // Default value

  igBegin("MENU", NULL, 0);
  igSeparatorText("Wire Select");

  if (igButton("Data bits", (ImVec2){0,0})) {
      igOpenPopup_Str("bits_popup", 0);
  }

  if (igBeginPopup("bits_popup", 0)) {
      for (int bits = 1; bits <= 64; bits *= 2)
          if (igSelectable_Bool(TextFormat("%d bits", bits), selected_bits == bits, 0, (ImVec2){0,0}))
              selected_bits = bits;
      igEndPopup();
  }
  igSameLine(0, -1);
  igText("%d bits", selected_bits);

  f32 color[4] = {inputs->color.r / 255.0f, inputs->color.g / 255.0f, inputs->color.b / 255.0f, 1.0f};
  if (igColorEdit4("Wire Color", color, ImGuiColorEditFlags_NoAlpha)) {
      inputs->color = (Color){(u8)(color[0] * 255), (u8)(color[1] * 255), (u8)(color[2] * 255), 255};
  }

  igCheckbox("Debug", &show_debug);

  igEnd();

  // Call debug function outside of the main menu window
  debug(world, &show_debug);

  igRender();
  ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
}
