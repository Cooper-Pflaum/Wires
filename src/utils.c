#include <math.h>
#include "types.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

f32 _clamp(f32 value, f32 min, f32 max) {
  return fmaxf(min, fminf(value, max));       // Force value to stay in range
}

v2 _snapToGrid(v2 pos, u16 cell_size) {
  return (v2){(u16)(pos.x / cell_size) * cell_size + cell_size / 2.0f, (u16)(pos.y / cell_size) * cell_size + cell_size / 2.0f}; //Set position to cell center
}

ImVec4 ColorToImVec4(Color color){
  return (ImVec4){
    color.r / 255.0f,
    color.g / 255.0f,
    color.b / 255.0f,
    color.a / 255.0f
  };
}
