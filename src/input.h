#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "../lib/types.h"
#include "../lib/consts.h"


// void HandleInput(DrawingState *state);
// void HandleDrawingInput(DrawingState *state, v2 mousePos);
// void HandleDrawingRelease(DrawingState *state, v2 mousePos);

void HandleInput(struct World *world, struct Input *inputs);
#endif // INPUT_H
