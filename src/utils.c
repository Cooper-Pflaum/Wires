#include <math.h>
#include "types.h"

f32 _clamp(f32 value, f32 min, f32 max) {
  return fmaxf(min, fminf(value, max));       // Force value to stay in range
}

v2 _snapToGrid(v2 pos, u16 cell_size) {
  return (v2){(u16)(pos.x / cell_size) * cell_size + cell_size / 2.0f, (u16)(pos.y / cell_size) * cell_size + cell_size / 2.0f}; //Set position to cell center
}

ImVec4 _ColorToImVec4(Color color){
  return (ImVec4){
    color.r / 255.0f,
    color.g / 255.0f,
    color.b / 255.0f,
    color.a / 255.0f
  };
}

bool _ColorEquals(Color c1, Color c2) {
  return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}
