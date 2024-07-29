#include <stdio.h>
#include <math.h>
#include <raylib.h>

#include "input.h"
#include "utils.h"
#include "render.h"
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
  v2 gridPos = {
    (u16)((mousePos.x - world->offset.x) / CELL_SIZE / world->zoom),
    (u16)((mousePos.y - world->offset.y) / CELL_SIZE / world->zoom) 
  };

  // Handle wire drawing
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (!inputs->isDrawing) {
      // First click: start drawing
      inputs->startPos = gridPos;
      inputs->isDrawing = true;
      inputs->directionSet = false;
    } else {
      // Second click: finish drawing
      inputs->endPos = gridPos;
      drawWire(world, inputs, false);  // Draw the final wire
      inputs->isDrawing = false;
    }
  }

  // Update preview wire
  if (inputs->isDrawing) {
    inputs->endPos = gridPos;
    
    if (!inputs->directionSet) {
      // Set direction based on first non-zero movement
      if (gridPos.x != inputs->startPos.x || gridPos.y != inputs->startPos.y) {
        inputs->direction = (fabs(gridPos.x - inputs->startPos.x) > fabs(gridPos.y - inputs->startPos.y));
        inputs->directionSet = true;
      }
    }

    // Draw the preview wire
    drawWire(world, inputs, true);
  }
}
