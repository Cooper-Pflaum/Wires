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

typedef struct {
  u8 state;     // Used for rotation of things like wires or gates
  u8 type;      // EMPTY, WIRE, GATE
  u8 databits;  // Bits across the gate or wire
  v2 pos;       // Position on the grid
  Color color;  // Color used for wire
} Cell;

struct World{
  bool menu_active;
  f32 zoom;
  v2 offset;
  Cell grid [GRID_WIDTH*GRID_HEIGHT];
};

struct Input{
  u8 type;
  Color color;
  v2 startPos;
  v2 endPos;
  bool isDrawing;
  bool direction; // horizontal=1 | vertical=0 
  bool directionSet;
};

#endif // TYPES_H
