#include <math.h>
#include "../include/types.h"

f32 _clamp(f32 value, f32 min, f32 max) {
  return fmaxf(min, fminf(value, max));       // Force value to stay in range
}

v2 _snapToGrid(v2 pos, u16 cell_size) {
  return (v2){(u16)(pos.x / cell_size) * cell_size + cell_size / 2.0f, (u16)(pos.y / cell_size) * cell_size + cell_size / 2.0f}; //Set position to cell center
}
