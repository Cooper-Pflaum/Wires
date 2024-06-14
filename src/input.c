#include <raylib.h>
#include <stdio.h>
#include <math.h> // Include math.h for fabs
#include "input.h"









void HandleInput(struct DrawingState *state) {
    Vector2 mousePos = GetMousePosition();
    Vector2 mouseDelta = GetMouseDelta();
    float mouseWheel = GetMouseWheelMove();

    // Handle zoom
    state->zoom += mouseWheel * 0.1f;
    if (state->zoom < 0.1f) state->zoom = 0.1f;
    if (state->zoom > 3.0f) state->zoom = 3.0f;

    // Handle panning
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        state->offset.x += mouseDelta.x;
        state->offset.y += mouseDelta.y;

        if (state->offset.x > 0) state->offset.x = 0;
        if (state->offset.y > 0) state->offset.y = 0;
        // if (state->offset.x < GetScreenWidth() * CELL_SIZE * GRID_WIDTH) state->offset.x = -GetScreenWidth() * CELL_SIZE * GRID_WIDTH - GetScreenWidth();
        // if (state->offset.y < GetScreenHeight() * CELL_SIZE * GRID_HEIGHT) state->offset.y = -GetScreenHeight() * CELL_SIZE * GRID_HEIGHT - GetScreenHeight();
    }

    // Handle drawing
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        HandleDrawingInput(state, mousePos);
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        HandleDrawingRelease(state, mousePos);
    }
}


void HandleDrawingInput(struct DrawingState *state, Vector2 mousePos) {
    if (!state->isDrawing) {
        state->startPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
        state->isDrawing = true;
        state->directionSet = false; // Reset direction when starting a new drawing
    }

    if (!state->directionSet) {
        // Determine initial direction based on the first significant movement
        state->drawHorizontalFirst = fabs(((mousePos.x - state->offset.x) / state->zoom) - state->startPos.x) >= fabs(((mousePos.y - state->offset.y) / state->zoom) - state->startPos.y);
        state->directionSet = true; // Set the direction
    }

    state->endPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });

    // Reset direction if the mouse returns to the starting square
    if (state->endPos.x == state->startPos.x && state->endPos.y == state->startPos.y) {
        state->directionSet = false;
    }
}

void HandleDrawingRelease(struct DrawingState *state, Vector2 mousePos) {
    state->endPos = SnapToGrid((v2){ (mousePos.x - state->offset.x) / state->zoom, (mousePos.y - state->offset.y) / state->zoom });
    if (state->endPos.x != state->startPos.x || state->endPos.y != state->startPos.y) {
        drawWire(state->startPos, state->endPos, state->drawHorizontalFirst, false); // Draw the final wire
        int endCellX = (int)(state->endPos.x / CELL_SIZE);
        int endCellY = (int)(state->endPos.y / CELL_SIZE);
        grid[endCellY][endCellX] = 1;
    }
    state->isDrawing = false;
}
