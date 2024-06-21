#ifndef TYPES_H
#define TYPES_H


#include <stdint.h>
#include <unistd.h>
#include "consts.h"
#include "raylib.h"


typedef float    f32;
typedef double   f64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef Vector2  v2;
typedef Vector3  v3;

typedef struct {
  u8 state;
  u8 type;
  v2 pos;
  Color color;
} Cell;

struct World{
  f32 zoom;
  v2 offset;
  Cell grid [GRID_WIDTH*GRID_HEIGHT];
};

struct Drawing{
  u8 type;
  u8 state;
  Color color;
  v2 startPos;
  v2 endPos;
  bool isDrawing;
  bool drawHorizontalFirst;
  bool directionSet;
};





// typedef int8_t   i8;
// typedef int16_t  i16;
// typedef int32_t  i32;
// typedef int64_t  i64;
// typedef size_t   usize;
// typedef ssize_t  isize;
// typedef uint32_t color;

// typedef struct v2_s {  f32 x, y;    } v2;
// typedef struct v3_s {  f32 x, y, z; } v3;

#endif // TYPES_H
