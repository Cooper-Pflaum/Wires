#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "utils.h"
#include "grid.h"
#include "input.h"
#include "../lib/types.h"
#include "../lib/consts.h"






void HandleInput(struct World *world, struct Input *inputs) {
  // Handle zoom
  float zoomDelta = GetMouseWheelMove() * 0.5f;
  world->zoom = _clamp(world->zoom + zoomDelta, 1.0f, 10.0f);

  // Handle panning
  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    v2 mouseDelta = GetMouseDelta();
    world->offset.x += mouseDelta.x;
    world->offset.y += mouseDelta.y;

    // Calculate bounds and clamp offset within bounds
    world->offset.x = _clamp(world->offset.x, W - CELL_SIZE * GRID_WIDTH * world->zoom, 0); // value, minX, maxX
    world->offset.y = _clamp(world->offset.y, H - CELL_SIZE * GRID_HEIGHT * world->zoom, 0); // value, minY, maxY
  }

  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    v2 mousePos = GetMousePosition();



    if(!inputs->isDrawing){
      inputs->startPos = (v2) {
        (u16)((mousePos.x - world->offset.x) / CELL_SIZE / world->zoom), 
        (u16)((mousePos.y - world->offset.y) / CELL_SIZE / world->zoom)
      };
      // inputs->startPos = _snapToGrid(inputs->startPos, CELL_SIZE);
      world->grid[(u32)(inputs->startPos.x + (inputs->startPos.y * GRID_WIDTH))].color = WHITE;
      world->grid[(u32)(inputs->startPos.x + (inputs->startPos.y * GRID_WIDTH))].type = 1;

      // inputs->startPos = _snapToGrid((v2){ (mousePos.x - world->offset.x) / world->zoom, (mousePos.y - world->offset.y) / world->zoom }, CELL_SIZE);
      DrawFPS(0,0);
      char posText[32];
      sprintf(posText, "Pos: %.1f, %.1f", inputs->startPos.x, inputs->startPos.y);
      DrawText(posText, 0, 40, 20, GREEN);
    }
  }
  else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
  
  }
}


  // mousePos.x -= MENU_OFFSET;

  // // Handle drawing
  // if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
  //     HandleDrawingInput(state, mousePos);
  // } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
  //     HandleDrawingRelease(state, mousePos);
  // }


// void HandleDrawingInput(DrawingState *state, v2 mousePos) {
//     if (!state->isDrawing) {
//     state->startPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
//         state->isDrawing = true;
//         state->directionSet = false; // Reset direction when starting a new drawing
//     }
//
//     if (!state->directionSet) {
//         // Determine initial direction based on the first significant movement
//         state->drawHorizontalFirst = fabs(((mousePos.x - state->offset.x) / state->zoom) - state->startPos.x) >= fabs(((mousePos.y - state->offset.y) / state->zoom) - state->startPos.y);
//         state->directionSet = true; // Set the direction
//     }
//
//     state->endPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
//
//     // Reset direction if the mouse returns to the starting square
//     if (state->endPos.x == state->startPos.x && state->endPos.y == state->startPos.y) {
//         state->directionSet = false;
//     }
// }
//
// void HandleDrawingRelease(DrawingState *state, v2 mousePos) {
//     state->endPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
//     if (state->endPos.x != state->startPos.x || state->endPos.y != state->startPos.y) {
//         drawWire(state, false, (Color){state->color.r, state->color.g, state->color.b, 100}); // Draw the final wire
//         int endCellX = (int)(state->endPos.x / CELL_SIZE);
//         int endCellY = (int)(state->endPos.y / CELL_SIZE);
//         grid[endCellY][endCellX] = 1;
//     }
//     state->isDrawing = false;
// }
