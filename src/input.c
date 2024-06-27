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
  world->zoom = _clamp(world->zoom + GetMouseWheelMove() * 0.5f, 0.5f, 10.0f);

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

  // Handle drawing wire
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
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


  char key = GetKeyPressed();                                    
  switch (key) {
    case '1':
      inputs->type  = 1;
      inputs->color = MAROON;
      break;
    case '2':
      inputs->type  = 1;
      inputs->color = ORANGE;
      break;
    case '3':
      inputs->type  = 1;
      inputs->color = YELLOW;
      break;
    case '4':
      inputs->type  = 1;
      inputs->color = LIME;
      break;
    case '5':
      inputs->type  = 1;
      inputs->color = BLUE;
      break;
    case '6':
      inputs->type  = 1;
      inputs->color = VIOLET;
      break;
    case '7':
      inputs->type  = 1;
      inputs->color = RAYWHITE;
      break;
    case '0':
      printf("BLACK");
      inputs->type  = 0;
      inputs->color = BLANK;
      break;
    default:
      // Handle unexpected case if needed
      break;
  }
}
