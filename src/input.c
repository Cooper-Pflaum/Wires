#include <stdio.h>
#include <math.h>
#include <raylib.h>

#include "utils.h"
#include "render.h"
#include "input.h"
#include "types.h"
#include "consts.h"

void HandleInput(World *world, Input *inputs) {
  // Handle zoom
  world->zoom = _clamp(world->zoom + GetMouseWheelMove() * 0.25f, 0.5f, 10.0f);

  // Handle panning
  if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
    v2 mouseDelta = GetMouseDelta();
    world->offset.x = _clamp(world->offset.x + mouseDelta.x, W - CELL_SIZE * GRID_WIDTH * world->zoom, 0);
    world->offset.y = _clamp(world->offset.y + mouseDelta.y, H - CELL_SIZE * GRID_HEIGHT * world->zoom, 0);
  }

  v2 mousePos = GetMousePosition();


  // Handle drawing wire
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    v2 gridPos = {
      (u16)((mousePos.x - world->offset.x) / CELL_SIZE / world->zoom),
      (u16)((mousePos.y - world->offset.y) / CELL_SIZE / world->zoom) 
    };
    if (!inputs->isDrawing) {
      inputs->startPos = gridPos;
      inputs->isDrawing = true;
      inputs->directionSet = false;
    } 
    else {
      // Check if we're back at the start position
      if (gridPos.x == inputs->startPos.x && gridPos.y == inputs->startPos.y) {
        inputs->directionSet = false;  // Allow direction to be reset
      }
      else if (!inputs->directionSet) {
        // Set direction based on first non-zero movement
        if (gridPos.x != inputs->startPos.x || gridPos.y != inputs->startPos.y) {
          inputs->direction = (fabs(gridPos.x - inputs->startPos.x) > fabs(gridPos.y - inputs->startPos.y));
          inputs->directionSet = true;
        }
      }
    }

    inputs->endPos = gridPos;

    // Draw the preview wire
    drawWire(world, inputs, true);
  }
  else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && inputs->isDrawing) {
    // Draw the final wire
    drawWire(world, inputs, false);
    inputs->isDrawing = false;
  }
}



