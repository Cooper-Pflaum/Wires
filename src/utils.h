#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "../include/types.h"

f32 _clamp(f32 value, f32 min, f32 max);
v2 _snapToGrid(v2 pos, u16 cell_size);

#endif // UTILS_H
