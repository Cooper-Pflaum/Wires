#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "raylib.h"
#include "utils.h"
#include "gui.h"
#include "input.h"
#include "types.h"
#include "consts.h"

CellArray initCellArray() {
  CellArray cellArray;
  cellArray.count = GRID_WIDTH * GRID_HEIGHT;
  cellArray.type =                     (cellType*)calloc(cellArray.count, sizeof(cellType));
  cellArray.state =                       (bool*) calloc(cellArray.count, sizeof(bool));
  cellArray.bit_size =                    (u8*)   calloc(cellArray.count, sizeof(u8));
  cellArray.connections =                 (uchar*)calloc(cellArray.count, sizeof(uchar));
  cellArray.color =                       (Color*)malloc(cellArray.count * sizeof(Color));
  cellArray.value =                       (u32*)  calloc(cellArray.count, sizeof(u32));
  cellArray.is_part_of_larger_component = (bool*) calloc(cellArray.count, sizeof(bool));
  cellArray.parent_component_id =         (u32*)  malloc(cellArray.count * sizeof(u32));

  // Initialize positions and colors
  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      int index = y * GRID_WIDTH + x;
      cellArray.color[index] = WHITE;
      cellArray.parent_component_id[index] = -1;
    }
  }
  return cellArray;
}

void freeCellArray(CellArray* cellArray) {
  free(cellArray->type);
  free(cellArray->state);
  free(cellArray->bit_size);
  free(cellArray->connections);
  free(cellArray->color);
  free(cellArray->value);
  free(cellArray->is_part_of_larger_component);
  free(cellArray->parent_component_id);
}

void updateGridCell(CellArray *cellArray, u32 x, u32 y, cellType type, Color color) {
  u32 index = x + (y * GRID_WIDTH);
  cellArray->type[index] = type;
  cellArray->color[index] = color;
}

void drawWire(World *world, Input *inputs, bool isPreview) {
  CellArray *cellArray = &world->grid;
  Color wireColor = isPreview ? ColorAlpha(inputs->wire_color, 0.5f) : inputs->wire_color;
  f32 cellSize = CELL_SIZE * world->zoom;

  // Calculate screen positions
  v2 startScreen = {
    inputs->startPos.x * cellSize + world->offset.x,
    inputs->startPos.y * cellSize + world->offset.y
  };
  v2 endScreen = {
    inputs->endPos.x * cellSize + world->offset.x,
    inputs->endPos.y * cellSize + world->offset.y
  };
  v2 cornerScreen = inputs->direction ? 
    (v2){endScreen.x, startScreen.y} : 
    (v2){startScreen.x, endScreen.y};

  if (isPreview) {
    // Draw preview segments directly within drawWire
    DrawRectangle(
      fminf(startScreen.x, cornerScreen.x) + cellSize / 3,
      fminf(startScreen.y, cornerScreen.y) + cellSize / 3,
      fabsf(cornerScreen.x - startScreen.x) + cellSize / 3,
      fabsf(cornerScreen.y - startScreen.y) + cellSize / 3,
      wireColor
    );
    DrawRectangle(
      fminf(cornerScreen.x, endScreen.x) + cellSize / 3,
      fminf(cornerScreen.y, endScreen.y) + cellSize / 3,
      fabsf(endScreen.x - cornerScreen.x) + cellSize / 3,
      fabsf(endScreen.y - cornerScreen.y) + cellSize / 3,
      wireColor
    );
  } else {
    int dx = (inputs->endPos.x > inputs->startPos.x) - (inputs->endPos.x < inputs->startPos.x);
    int dy = (inputs->endPos.y > inputs->startPos.y) - (inputs->endPos.y < inputs->startPos.y);
    int x = inputs->startPos.x, y = inputs->startPos.y;

    do {
      updateGridCell(cellArray, x, y, WIRE, wireColor);
      if (x != inputs->endPos.x && (inputs->direction || y == inputs->endPos.y)) x += dx;
      else if (y != inputs->endPos.y) y += dy;
    } while (x != inputs->endPos.x || y != inputs->endPos.y);

    updateGridCell(cellArray, inputs->endPos.x, inputs->endPos.y, WIRE, wireColor);
  }
}

void drawGrid(World *world) {
  f32 invZoom = 1.0f / world->zoom;
  f32 offsetX = -world->offset.x * invZoom;
  f32 offsetY = -world->offset.y * invZoom;

  u16 startX = (u16)fmaxf((f32)(offsetX / CELL_SIZE), 0.0f);
  u16 startY = (u16)fmaxf((f32)(offsetY / CELL_SIZE), 0.0f);
  u16 endX = (u16)fminf((f32)((offsetX + world->screenSize.x * invZoom) / CELL_SIZE), (f32)(GRID_WIDTH - 1));
  u16 endY = (u16)fminf((f32)((offsetY + world->screenSize.y * invZoom) / CELL_SIZE), (f32)(GRID_HEIGHT - 1));

  for (u16 y = startY; y <= endY; y++) {
    for (u16 x = startX; x <= endX; x++) {
      u32 index = x + (y * GRID_WIDTH);
      
      if (world->gui.show_debug_lines) {
        DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
      }

      if (world->grid.type[index] != EMPTY) {
        Color currentColor = world->grid.color[index];
        DrawRectangle(x * CELL_SIZE + CELL_SIZE/3, y * CELL_SIZE + CELL_SIZE/3, CELL_SIZE/3, CELL_SIZE/3, currentColor);

        // Draw connections
        if (x > 0 && ColorEquals(world->grid.color[index-1], currentColor))
          DrawRectangle(x * CELL_SIZE, y * CELL_SIZE + CELL_SIZE/3, CELL_SIZE/3, CELL_SIZE/3, currentColor);
        if (x < GRID_WIDTH-1 && ColorEquals(world->grid.color[index+1], currentColor))
          DrawRectangle(x * CELL_SIZE + 2*CELL_SIZE/3, y * CELL_SIZE + CELL_SIZE/3, CELL_SIZE/3, CELL_SIZE/3, currentColor);
        if (y > 0 && ColorEquals(world->grid.color[index-GRID_WIDTH], currentColor))
          DrawRectangle(x * CELL_SIZE + CELL_SIZE/3, y * CELL_SIZE, CELL_SIZE/3, CELL_SIZE/3, currentColor);
        if (y < GRID_HEIGHT-1 && ColorEquals(world->grid.color[index+GRID_WIDTH], currentColor))
          DrawRectangle(x * CELL_SIZE + CELL_SIZE/3, y * CELL_SIZE + 2*CELL_SIZE/3, CELL_SIZE/3, CELL_SIZE/3, currentColor);
      }
    }
  }
}


void render(World *world, Input *inputs) {
  ClearBackground((Color){0.0f, 0.0f, 0.0f, 1.0f});
  BeginDrawing();

  // Raylib  
  BeginMode2D((Camera2D){ .offset = world->offset, .target = {0, 0}, .rotation = 0.0f, .zoom = world->zoom});  
    drawGrid(world);
  EndMode2D();

  // ImGUI
  drawGUI(world, inputs);

  EndDrawing();
}
