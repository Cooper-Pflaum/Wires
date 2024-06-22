#ifndef UTILS_H
#define UTILS_H

#include <math.h>

static inline float Clamp(float value, float min, float max) {
    return fmaxf(min, fminf(value, max));
}

// You can add other utility functions here as needed

#endif // UTILS_H
