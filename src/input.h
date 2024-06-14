#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "grid.h"


struct DrawingState {
    v2 startPos;
    v2 endPos; 
    bool isDrawing;
    bool drawHorizontalFirst;
    bool directionSet;
    float zoom;
    Vector2 offset;
};


void HandleInput(struct DrawingState *state);

void HandleDrawingInput(struct DrawingState *state, Vector2 mousePos);

void HandleDrawingRelease(struct DrawingState *state, Vector2 mousePos);

#endif // INPUT_H
