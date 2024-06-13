#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "grid.h"

void HandleInput(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, bool *directionSet, float *zoom, Vector2 *offset);

void HandleDrawingInput(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, bool *directionSet, Vector2 mousePos, Vector2 *offset, float *zoom);

void HandleDrawingRelease(v2 *startPos, v2 *endPos, bool *isDrawing, bool *drawHorizontalFirst, Vector2 mousePos, Vector2 *offset, float *zoom);

#endif // INPUT_H
