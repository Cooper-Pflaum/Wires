#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "types.h"

#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

f32 _clamp(f32 value, f32 min, f32 max);
v2 _snapToGrid(v2 pos, u16 cell_size);
ImVec4 ColorToImVec4(Color color);
#endif // UTILS_H
