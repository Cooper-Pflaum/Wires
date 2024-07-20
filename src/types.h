#ifndef TYPES_H
#define TYPES_H
#define MAX_CUSTOM_COLORS 16

#include <stdint.h>
#include <unistd.h>
#include "consts.h"
#include "raylib.h"
#include "../lib/raylib-cimgui/imgui_impl_raylib.h"

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned char uchar;
typedef Vector2  v2;

// typedef struct {
//   u8 state;     // Used for rotation of things like wires or gates
//   u8 type;      // EMPTY, WIRE, GATE
//   u8 databits;  // Bits across the gate or wire
//   v2 pos;       // Position on the grid
//   Color color;  // Color used for wire
// } Cell;

// Enum for cell types
typedef enum {
  EMPTY,
  WIRE,
  INPUT,
  OUTPUT,
  GATE_PART
} CellType;

// Enum for gate types
typedef enum {
  GATE_AND,
  GATE_OR,
  GATE_NOT,
  GATE_XOR,
  // Add other gate types as needed
} GateType;

// Structure for the small cell
typedef struct {
  CellType type;
  bool state;
  v2 pos;
  u8 bit_size;
  uchar connections;  // Bitfield for connections: 0bUDLR (Up, Down, Left, Right)
  Color color;  // Color used for wire
  unsigned long long value;
  bool is_part_of_larger_component;
  int parent_component_id;
} Cell;

// Structure for the larger component (e.g., 3x3 gates)
typedef struct {
  int id;
  GateType type;
  int top_left_x;
  int top_left_y;
  Cell* cells[3][3];  // Pointers to the 9 cells this component occupies
  int input_count;
  int output_count;
  // You might want to add more specific properties for gates here
} LargeComponent;

// Enum for drawing modes
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
    char name[32];
    Color color;
} CustomColor;


typedef struct {
    bool show_debug;
    u8 selected_bits;
    Color wire_color;
    Color custom_color;
    bool show_bits_popup;
    CustomColor saved_colors[MAX_CUSTOM_COLORS];
    int num_saved_colors;
} GUI;

typedef struct {
    v2 screenSize;
    bool menu_active;
    f32 zoom;
    v2 offset;
    Cell grid[GRID_HEIGHT*GRID_WIDTH];
    DrawMode current_draw_mode;
    LargeComponent* large_components;  // Dynamic array of large components
    // u64 large_component_count;
    // int large_component_capacity;
    // int next_component_id;  // For generating unique IDs for large components
    GUI gui;
} World;

struct Input{
  u8 type;
  Color wire_color;
  v2 startPos;
  v2 endPos;
  bool isDrawing;
  bool direction; // horizontal=1 | vertical=0 
  bool directionSet;
};




#endif // TYPES_H
