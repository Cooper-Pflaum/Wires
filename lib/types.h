#ifndef TYPES_H
#define TYPES_H


#include <stdint.h>
#include <unistd.h>
#include "raylib.h"


typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uint8_t  byte;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef size_t   usize;
typedef ssize_t  isize;
typedef uint32_t color;

typedef Vector2  v2;
typedef Vector3  v3;
// typedef struct v2_s {  f32 x, y;    } v2;
// typedef struct v3_s {  f32 x, y, z; } v3;

typedef struct {
    v2 startPos;
    v2 endPos;
    bool isDrawing;
    bool drawHorizontalFirst;
    bool directionSet;
    float zoom;
    Vector2 offset;
} DrawingState;


#endif // TYPES_H
