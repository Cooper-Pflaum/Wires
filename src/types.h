#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "consts.h"
#include "raylib.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

typedef float         f32;
typedef double        f64;
typedef uint8_t       u8;
typedef uint16_t      u16;
typedef uint32_t      u32;
typedef uint64_t      u64;
typedef unsigned char uchar;
typedef Vector2       v2;

typedef enum {
  EMPTY,
  WIRE,
  INPUT,
  OUTPUT,
  GATE
} cellType;

typedef enum {
  AND_GATE,
  OR_GATE,
  NOT_GATE,
  XOR_GATE,
} GateType;

typedef enum {
  DRAW_EMPTY,
  DRAW_WIRE,
  DRAW_INPUT,
  DRAW_OUTPUT,
  DRAW_AND_GATE,
  DRAW_OR_GATE,
  DRAW_NOT_GATE,
  // Add other drawing modes as needed
} DrawMode;

typedef struct {
  u8 selected_bits;
  bool show_debug;
  bool show_bits_popup;
  bool show_debug_lines;
  Color wire_color;
} GUI;


typedef struct {
  u8 type;
  Color wire_color;
  v2 startPos;
  v2 endPos;
  bool isDrawing;
  bool direction; // horizontal=1 | vertical=0 
  bool directionSet;
} Input;

// Separate arrays for each attribute of Cell
typedef struct {
  cellType* type;
  u32* value;
  u32* parent_component_id;
  u8* bit_size;
  uchar* connections;  // Bitfield for connections: 0bUDLR (Up, Down, Left, Right)
  Color* color;  // Color used for wire
  bool* state;
  bool* is_part_of_larger_component;
  size_t count;  // Number of cells
} CellArray;

// Separate arrays for each attribute of LargeComponent
typedef struct {
  u32* id;
  u32* top_left_x;
  u32* top_left_y;
  u8* input_count;
  u8* output_count;
  size_t count;  // Number of large components
  // Cell** cells[3][3];  // Pointers to the 9 cells this component occupies
  GateType* type;
} GateArray;

typedef struct {
    v2 screenSize;
    bool menu_active;
    f32 zoom;
    v2 offset;
    CellArray grid;
    DrawMode current_draw_mode;
    GateArray large_components;
    GUI gui;
} World;
#endif // TYPES_H
