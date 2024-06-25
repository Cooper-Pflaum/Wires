#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "utils.h"
#include "grid.h"
#include "input.h"
#include "../lib/types.h"
#include "../lib/consts.h"



void drawGrid(struct World *world){
  // Precompute values to reduce redundant calculations
  f32 invZoom = 1.0f / world->zoom;
  f32 offsetX = -world->offset.x * invZoom;
  f32 offsetY = -world->offset.y * invZoom;

  // Calculate the visible area based on the zoom level and offset
  u16 startX = (u16)fmaxf((f32)(offsetX / CELL_SIZE), 0.0f);
  u16 startY = (u16)fmaxf((f32)(offsetY / CELL_SIZE), 0.0f);
  u16 endX   = (u16)fminf((f32)((offsetX + W * invZoom) / CELL_SIZE) + 1.0f, (f32)(GRID_WIDTH - 1));
  u16 endY   = (u16)fminf((f32)((offsetY + H * invZoom) / CELL_SIZE) + 1.0f, (f32)(GRID_HEIGHT - 1));

  // Draw only the visible cells
  for (u16 x = startX; x <= endX; x++) {
    for (u16 y = startY; y <= endY; y++) {
      if(world->grid[x+(y*GRID_WIDTH)].type != 0){
        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, world->grid[x + (y * GRID_WIDTH)].color);
      }
    }
  }
}


void drawWire(struct World *world, struct Input *inputs, bool isPreview) {
  v2 currentPos = inputs->startPos;
  Color wireColor = isPreview ? (Color){255, 0, 0, 100} : RED; // Semi-transparent white for preview, solid white for final

  while (currentPos.x != inputs->endPos.x || currentPos.y != inputs->endPos.y) {
    u32 index = (u32)(currentPos.x + (currentPos.y * GRID_WIDTH));
    if (isPreview) {
      // For preview, just draw the wire without updating the grid
      DrawRectangle((u32)(currentPos.x * CELL_SIZE), (u32)(currentPos.y * CELL_SIZE), CELL_SIZE, CELL_SIZE, wireColor);
    } else {
      // For final wire, update the grid
      world->grid[index].type = 1;
      world->grid[index].color = wireColor;
    }

    // Update the current position
    if (inputs->direction) {
      // Move horizontally first
      if (currentPos.x != inputs->endPos.x) {
        currentPos.x += (inputs->endPos.x > currentPos.x) ? 1 : -1;
      } else {
        currentPos.y += (inputs->endPos.y > currentPos.y) ? 1 : -1;
      }
    } else {
      // Move vertically first
      if (currentPos.y != inputs->endPos.y) {
        currentPos.y += (inputs->endPos.y > currentPos.y) ? 1 : -1;
      } else {
        currentPos.x += (inputs->endPos.x > currentPos.x) ? 1 : -1;
      }
    }
  }

  // Draw the last cell
  u32 lastIndex = (u32)(currentPos.x + (currentPos.y * GRID_WIDTH));
  if (isPreview) {
    DrawRectangle(
      (u16)(currentPos.x * CELL_SIZE),
      (u16)(currentPos.y * CELL_SIZE),
      CELL_SIZE,
      CELL_SIZE,
      wireColor
    );
  } else {
    world->grid[lastIndex].type = 1;
    world->grid[lastIndex].color = wireColor;
  }
}
