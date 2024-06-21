#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "../lib/types.h"
#include "../lib/consts.h"
#include "grid.h"
#include "input.h"


// Cell grid [GRID_WIDTH*GRID_HEIGHT];


// v2 SnapToGrid(Vector2 pos) {
//     return (v2){(int)(pos.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f, (int)(pos.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE / 2.0f};
// }
//
//
// void drawCell(v2 pos, bool isPreview, Color wireColor) {
//     int xIdx = (int)(pos.x / CELL_SIZE);
//     int yIdx = (int)(pos.y / CELL_SIZE);
//     if (!isPreview) grid[yIdx][xIdx] = 1;
//     DrawRectangleRec((Rectangle){pos.x - CELL_SIZE / 2.0f, pos.y - CELL_SIZE / 2.0f, CELL_SIZE, CELL_SIZE}, wireColor);
// }
//
// void drawLine(v2 *currentPos, v2 endPos, bool horizontalFirst, bool isPreview, Color wireColor) {
//     if (horizontalFirst) {
//         while (currentPos->x != endPos.x) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->x += (endPos.x > currentPos->x) ? CELL_SIZE : -CELL_SIZE;
//         }
//         while (currentPos->y != endPos.y) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->y += (endPos.y > currentPos->y) ? CELL_SIZE : -CELL_SIZE;
//         }
//     } else {
//         while (currentPos->y != endPos.y) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->y += (endPos.y > currentPos->y) ? CELL_SIZE : -CELL_SIZE;
//         }
//         while (currentPos->x != endPos.x) {
//             drawCell(*currentPos, isPreview, wireColor);
//             currentPos->x += (endPos.x > currentPos->x) ? CELL_SIZE : -CELL_SIZE;
//         }
//     }
//     drawCell(endPos, isPreview, wireColor); // Draw the final cell
// }
//
// void drawWire(DrawingState *state, bool isPreview, Color wire_color) {
//     v2 currentPos = state->startPos;
//     Color wireColor = isPreview ? wire_color : BLACK;
//     drawLine(&currentPos, state->endPos, state->drawHorizontalFirst, isPreview, wireColor);
// }
//
//
// void drawGrid(DrawingState *state) {
//     // Calculate the visible area based on the zoom level and offset
//     int startX = fmax(-1 * (int)(state->offset.x / CELL_SIZE / state->zoom), 0);
//     int startY = fmax(-1 * (int)(state->offset.y / CELL_SIZE / state->zoom), 0);
//     int endX   = fmin((int)((-1 * state->offset.x) + (GetScreenWidth()) / state->zoom / CELL_SIZE) + 1, GRID_WIDTH - 1);
//     int endY   = fmin((int)((-1 * state->offset.y) + GetScreenHeight() / state->zoom / CELL_SIZE) + 1, GRID_HEIGHT - 1);
//
//     // Draw only the visible cells
//     for(int y = startY; y <= endY; y++) {
//       for(int x = startX; x <= endX; x++) {
//         Rectangle cellRect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
//         if (grid[y][x]) {
//           DrawRectangleRec(cellRect, WHITE); // Draw filled cell
//         } else if (state->zoom > 1.0) {
//           // DrawPixel(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2, LIGHTGRAY); // Draw a single point
//         }
//       }
//     }
// }
