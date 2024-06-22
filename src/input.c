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
    world->zoom = Clamp(world->zoom + zoomDelta, 1.0f, 10.0f);

    // Handle panning
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        v2 mouseDelta = GetMouseDelta();
        world->offset.x += mouseDelta.x;
        world->offset.y += mouseDelta.y;

        // Calculate bounds
        float maxOffsetX = 0;
        float maxOffsetY = 0;
        float minOffsetX = W - CELL_SIZE * GRID_WIDTH * world->zoom;
        float minOffsetY = H - CELL_SIZE * GRID_HEIGHT * world->zoom;

        // Clamp offset within bounds
        world->offset.x = Clamp(world->offset.x, minOffsetX, maxOffsetX);
        world->offset.y = Clamp(world->offset.y, minOffsetY, maxOffsetY);
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
//         state->startPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
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
