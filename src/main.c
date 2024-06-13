#include "raylib.h"
#include "grid.h"
#include "input.h"

int main() {
SetTraceLogLevel(LOG_ERROR); 
    InitWindow(1920,1080, "Drawable Grid");
    SetTargetFPS(60);

    v2 startPos = { 0, 0 };
    v2 endPos = { 0, 0 };
    bool isDrawing = false;
    bool drawHorizontalFirst = true;
    bool directionSet = false;

    float zoom = 1.0f;
    Vector2 offset = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D((Camera2D){ .offset = { offset.x, offset.y }, .target = { 0, 0 }, .rotation = 0.0f, .zoom = zoom });

        HandleInput(&startPos, &endPos, &isDrawing, &drawHorizontalFirst, &directionSet, &zoom, &offset);
        drawGrid(zoom, offset);

        if (isDrawing) {
            drawWire(startPos, endPos, drawHorizontalFirst, true); // Draw the wire preview
        }

        EndMode2D();
        DrawFPS(0,0);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
