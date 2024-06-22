#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "utils.h"
#include "grid.h"
#include "input.h"
#include "../lib/types.h"
#include "../lib/consts.h"




// v2 SnapToGrid(Vector2 pos) {
//     return (v2){(int)(pos.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f, (int)(pos.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f};
// }


// void drawCell(v2 pos, bool isPreview, Color wireColor) {
//     int xIdx = (int)(pos.x / CELL_SIZE);
//     int yIdx = (int)(pos.y / CELL_SIZE);
//     if (!isPreview) grid[yIdx][xIdx] = 1;
//     DrawRectangleRec((Rectangle){pos.x - CELL_SIZE / 2.0f, pos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
// }

// void drawLine(v2 *currentPos, v2 endPos, bool horizontalFirst, bool isPreview, Color wireColor) {
//     if (horizontalFirst) {
//         while (currentPos->x != endPos.x) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->x += (endPos.x > currentPos->x) ? CELL_SIZE : -CELL_SIZE;
//         }
//         while (currentPos->y != endPos.y) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->y += (endPos.y > currentPos->y) ? CELL_SIZE : -CELL_SIZE;
//         }
//     } else {
//         while (currentPos->y != endPos.y) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->y += (endPos.y > currentPos->y) ? CELL_SIZE : -CELL_SIZE;
//         }
//         while (currentPos->x != endPos.x) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->x += (endPos.x > currentPos->x) ? CELL_SIZE : -CELL_SIZE;
//         }
//     }
//     drawCell(endPos, isPreview, wireColor); // Draw the final cell
// }

// void drawWire(DrawingState *state, bool isPreview, Color wire_color) {
//     v2 currentPos = state->startPos;
//     Color wireColor = isPreview ? wire_color : BLACK;
//     drawLine(&currentPos, state->endPos, state->drawHorizontalFirst, isPreview, wireColor);
// }


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
      DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, world->grid[x + (y * GRID_WIDTH)].color);
    }
  }
}

