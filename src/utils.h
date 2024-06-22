#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "../lib/types.h"

inline f32 Clamp(f32 value, f32 min, f32 max) {
    return fmaxf(min, fminf(value, max));
}


#endif // UTILS_H
