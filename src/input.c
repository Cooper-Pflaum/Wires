#include "input.h"
#include <math.h> // Include math.h for fabs
#include <stdio.h>

void HandleInput(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, bool *directionSet, float *zoom, Vector2 *offset) {
    Vector2 mousePos = GetMousePosition();
    // printf("Mouse Pos: %f, %f\n", mousePos.x, mousePos.y);
    Vector2 mouseDelta = GetMouseDelta();
    float mouseWheel = GetMouseWheelMove();

    // Handle zoom
    *zoom += mouseWheel * 0.1f; // Zoom in/out based on mouse wheel scroll
    if (*zoom < 0.1f) *zoom = 0.1f; // Prevent zooming out too much
    if (*zoom > 3.0f) *zoom = 3.0f; // Prevent zooming in too much

    // Handle panning
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        offset->x += mouseDelta.x / *zoom;
        offset->y += mouseDelta.y / *zoom;

        if(offset->x > 0) offset->x = 0;
        if(offset->y > 0) offset->y = 0;
      
    }

    // Handle drawing
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        HandleDrawingInput(startPos, endPos, isDrawing, drawHorizontalFirst, directionSet, mousePos, offset, zoom);
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        HandleDrawingRelease(startPos, endPos, isDrawing, drawHorizontalFirst, mousePos, offset, zoom);
    }
}

void HandleDrawingInput(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, bool *directionSet, Vector2 mousePos, Vector2 *offset, float *zoom) {
    if (!*isDrawing) {
        *startPos = SnapToGrid((v2){ (mousePos.x - offset->x) / *zoom, (mousePos.y - offset->y) / *zoom });
        *isDrawing = true;
        *directionSet = false; // Reset direction when starting a new drawing
    }

    if (!*directionSet) {
        // Determine initial direction based on the first significant movement
        *drawHorizontalFirst = fabs(((mousePos.x - offset->x) / *zoom) - startPos->x) >= fabs(((mousePos.y - offset->y) / *zoom) - startPos->y);
        *directionSet = true; // Set the direction
    }

    *endPos = SnapToGrid((v2){ (mousePos.x - offset->x) / *zoom, (mousePos.y - offset->y) / *zoom });

    // Reset direction if the mouse returns to the starting square
    if (endPos->x == startPos->x && endPos->y == startPos->y) {
        *directionSet = false;
    }
}

void HandleDrawingRelease(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, Vector2 mousePos, Vector2 *offset, float *zoom) {
    *endPos = SnapToGrid((v2){ (mousePos.x - offset->x) / *zoom, (mousePos.y - offset->y) / *zoom });
    if (endPos->x != startPos->x || endPos->y != startPos->y) {
        drawWire(*startPos, *endPos, *drawHorizontalFirst, false); // Draw the final wire
        int endCellX = (int)(endPos->x / CELL_SIZE);
        int endCellY = (int)(endPos->y / CELL_SIZE);
        grid[endCellY][endCellX] = 1;
    }
    *isDrawing = false;
}
