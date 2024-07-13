#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "utils.h"
#include "grid.h"
#include "input.h"

#include "types.h"
#include "consts.h"



void drawGrid(World *world){
  // Precompute values to reduce redundant calculations
  f32 invZoom = 1.0f / world->zoom;
  f32 offsetX = -world->offset.x * invZoom;
  f32 offsetY = -world->offset.y * invZoom;

  // Calculate the visible area based on the zoom level and offset
  u16 startX = (u16)fmaxf((f32)(offsetX / CELL_SIZE), 0.0f);
  u16 startY = (u16)fmaxf((f32)(offsetY / CELL_SIZE), 0.0f);
  u16 endX   = (u16)fminf((f32)((offsetX + world->screenSize.x * invZoom) / CELL_SIZE), (f32)(GRID_WIDTH - 1));
  u16 endY   = (u16)fminf((f32)((offsetY + world->screenSize.y * invZoom) / CELL_SIZE), (f32)(GRID_HEIGHT - 1));

  // Draw only the visible cells
  for (u16 x = startX; x <= endX; x++) {
    for (u16 y = startY; y <= endY; y++) {
      if(world->grid[x+(y*GRID_WIDTH)].type != 0){
        DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, world->grid[x + (y * GRID_WIDTH)].color);
      }
    }
  }
}

void drawSegment(v2 from, v2 to, f32 cellSize, Color color) {
    DrawRectangle(
        fminf(from.x, to.x),
        fminf(from.y, to.y),
        fabsf(to.x - from.x) + cellSize,
        fabsf(to.y - from.y) + cellSize,
        color
    );
}

void updateGridCell(World *world, int x, int y, int type, Color color) {
    u32 index = x + (y * GRID_WIDTH);
    world->grid[index].type = type;
    world->grid[index].color = color;
}

void drawWire(World *world, struct Input *inputs, bool isPreview) {
    Color wireColor = isPreview ? (Color){inputs->color.r, inputs->color.g, inputs->color.b, 100} : inputs->color;
    f32 cellSize = CELL_SIZE * world->zoom;
    
    // Calculate screen positions
    v2 startScreen = {inputs->startPos.x * cellSize + world->offset.x, inputs->startPos.y * cellSize + world->offset.y};
    v2 endScreen =   {inputs->endPos.x * cellSize + world->offset.x, inputs->endPos.y * cellSize + world->offset.y};
    v2 cornerScreen = inputs->direction ? (v2){endScreen.x, startScreen.y} : (v2){startScreen.x, endScreen.y};

    if (isPreview) {
        // Draw preview using screen coordinates
        drawSegment(startScreen, cornerScreen, cellSize, wireColor);
        drawSegment(cornerScreen, endScreen, cellSize, wireColor);
    } else {
      // Use grid coordinates for actual wire placement
      u32 dx = (inputs->endPos.x > inputs->startPos.x) - (inputs->endPos.x < inputs->startPos.x);
      u32 dy = (inputs->endPos.y > inputs->startPos.y) - (inputs->endPos.y < inputs->startPos.y);
      u32 x = inputs->startPos.x, y = inputs->startPos.y;

      if (inputs->direction) {
        for (; x != inputs->endPos.x; x += dx) updateGridCell(world, x, y, inputs->type, wireColor);
        for (; y != inputs->endPos.y; y += dy) updateGridCell(world, x, y, inputs->type, wireColor);
      } else {
        for (; y != inputs->endPos.y; y += dy) updateGridCell(world, x, y, inputs->type, wireColor);
        for (; x != inputs->endPos.x; x += dx) updateGridCell(world, x, y, inputs->type, wireColor);
      }
      updateGridCell(world, inputs->endPos.x, inputs->endPos.y, inputs->type, wireColor);
    }
}
