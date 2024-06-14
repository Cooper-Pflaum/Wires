#include <stdio.h>
#include "raylib.h"
#include "grid.h"
#include "input.h"

#define W 1920
#define H 1080


int main() {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(W, H, "Drawable Grid");

    struct DrawingState state = {
        .startPos = { 0, 0 },
        .endPos = { 0, 0 },
        .isDrawing = false,
        .drawHorizontalFirst = true,
        .directionSet = false,
        .zoom = 1.0f,
        .offset = { 0.0f, 0.0f }
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D((Camera2D){ .offset = { state.offset.x, state.offset.y }, .target = { 0, 0 }, .rotation = 0.0f, .zoom = state.zoom });

        HandleInput(&state);

        if (state.isDrawing) {
            drawWire(state.startPos, state.endPos, state.drawHorizontalFirst, true);
        }

        drawGrid(state.zoom, state.offset);

        EndMode2D();
        DrawFPS(0, 0);
        char zoomText[32];
        sprintf(zoomText, "Zoom: %.2f", state.zoom);
        DrawText(zoomText, 0, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
